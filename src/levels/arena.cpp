#include "arena.hpp"
#include "rendering/background.hpp"
#include "ships/aiShip.hpp"

// #include "prefabs/prefabs.hpp"

namespace levels
{
	void Arena::recordFrame()
	{
		draw();
		sf::Texture texture;
		texture.create(config::SCREEN_WIDTH, config::SCREEN_HEIGHT);
		texture.update(*globals::WINDOW);
		sf::Image image = texture.copyToImage();
		cv::Mat frame(image.getSize().y, image.getSize().x, CV_8UC4, (void *)image.getPixelsPtr());
		cv::cvtColor(frame, frame, cv::COLOR_RGBA2BGR); // Convert to BGR format which OpenCV expects
		videoWriter->write(frame);
	}

	void Arena::setTactics(const Tactics &tactics)
	{
		int tacticsUsed = 0;

		for (const auto &ship : aiShips)
		{
			if (not ship->isNeuralNetwork())
				continue;
			ship->setTactic(tactics[tacticsUsed]);
			++tacticsUsed;
		}
		if (tacticsUsed < tactics.size())
		{
			std::cout << "Error not all tactics used!!! tactics used " << tacticsUsed << " tactics size " << tactics.size() << std::endl;
		}
	}
	Arena::Rewards Arena::makeRewards(const std::vector<int> &hps)
	{
		std::vector<int> hpDelta{};
		float redTeamHpDelta = 0;
		float blueTeamHpDelta = 0;

		for (int i = 0; i < aiShips.size(); ++i)
		{
			const auto &ship = *(aiShips[i]);
			int delta = ship.getHp() - hps[i];
			hpDelta.push_back(delta);
			if (ship.getTeam() == redTeam)
				redTeamHpDelta += delta;
			else
				blueTeamHpDelta += delta;
		}
		float redTeamAvgReward = redTeamHpDelta / redTeamShips.size();
		float blueTeamAvgReward = blueTeamHpDelta / blueTeamShips.size();

		Rewards rewards{};

		for (int i = 0; i < aiShips.size(); ++i)
		{
			if (not aiShips[i]->isNeuralNetwork())
				continue;

			float reward = hpDelta[i] - (aiShips[i]->getTeam() == redTeam ? blueTeamAvgReward : redTeamAvgReward);
			rewards.push_back(hpDelta[i]);
		}
		return rewards;
	}

	Arena::StepType Arena::step(const Tactics &tactics, int frameSkip)
	{
		setTactics(tactics);
		Dones dones{}; // todo make it not fake

		std::vector<int> hps;
		for (const auto &ship : aiShips)
			hps.push_back(ship->getHp());

		for (int i = 0; i < frameSkip; ++i)
		{
			frameUpdate();

			if (recordVideo)
				recordFrame();
		}

		// todo cleanupDeads();
		for (auto &ships : aiShips)
		{
			if (ships->isNeuralNetwork())
				dones.push_back(0);
		}
		return std::make_tuple(make_obs(), makeRewards(hps), dones);
	}
	Arena::Observations Arena::reset(bool recordEpisode)
	{
		++episodeNumber;
		if (videoWriter)
		{
			globals::WINDOW->close();
			videoWriter->release();
		}
		recordVideo = recordEpisode;

		if (recordVideo)
		{
			initRendering();
			std::string dirName = "Trainings/Starships/videos/";
			std::string fileName = dirName + "output_" + std::to_string(episodeNumber) + ".avi";
			videoWriter = std::make_shared<cv::VideoWriter>(fileName, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 60, cv::Size(config::SCREEN_WIDTH, config::SCREEN_HEIGHT));
			std::cout << "Recording episode....Opening writer success? " << videoWriter->isOpened() << std::endl;
		}

		clear();

		auto background = std::make_shared<rendering::Background>(prefabs::background);

		auto lasher_blue = std::make_shared<ships::AiShip>(prefabs::lasher, blueTeam, sf::Vector2f{200, (float)(rand() % 1600 - 800)}, sf::Vector2f{0, 0}, 0);
		auto lasher2_blue = std::make_shared<ships::AiShip>(prefabs::lasher, blueTeam, sf::Vector2f{400, (float)(rand() % 1600 - 800)}, sf::Vector2f{0, 0}, 0, true);
		auto scarab_blue = std::make_shared<ships::AiShip>(prefabs::scarab, blueTeam, sf::Vector2f{600, (float)(rand() % 1600 - 800)}, sf::Vector2f{0, 0}, 0, true);

		auto lasher_red = std::make_shared<ships::AiShip>(prefabs::lasher, redTeam, sf::Vector2f{800, (float)(rand() % 400 - 200)}, sf::Vector2f{0, 0}, 0.f, true);
		auto hammerhead_red = std::make_shared<ships::AiShip>(prefabs::hammerhead, redTeam, sf::Vector2f{0, (float)(rand() % 400 - 200)}, sf::Vector2f{0, 0}, 0.f, true);

		addObject(background);

		addObject(lasher_blue, lasher_blue->getTeam());
		addObject(lasher2_blue, lasher2_blue->getTeam());
		addObject(scarab_blue, scarab_blue->getTeam());

		addObject(lasher_red, lasher_red->getTeam());
		addObject(hammerhead_red, hammerhead_red->getTeam());

		populateArenaWithAsteroids(asteroids_number);

		return make_obs();
	}
	Arena::Observations Arena::make_obs()
	{
		ObservationFactory obsFactory{};
		return obsFactory.makeObservations(aiShips);
	}

	void Arena::populateArenaWithAsteroids(int n)
	{
		constexpr int safeDistance = 100;

		auto getRandomAsteroidPrefab = []() -> const prefabs::CollidablePrefab &
		{
			int r = getRandomNumber(0, 100);
			return (r > 80) ? prefabs::asteroidBig2 : (r > 40) ? prefabs::asteroid2
															   : prefabs::asteroid3;
		};

		for (int i = 0; i < n;)
		{
			const auto &prefab = getRandomAsteroidPrefab();
			float xx = static_cast<float>(getRandomNumber(-x, x));
			float yy = static_cast<float>(getRandomNumber(-y, y));
			float vX = getRandomNumber(-prefab.maxVelocity, prefab.maxVelocity);
			float vY = getRandomNumber(-prefab.maxVelocity, prefab.maxVelocity);
			auto asteroid = std::make_shared<rendering::CollisionObject>(prefab, sf::Vector2f{xx, yy}, sf::Vector2f{vX, vY});

			for (const auto &obj : collidables)
			{
				if (physics::collisionHappening(obj->getCollisionCircle(), {{xx, yy}, asteroid->getRadius() + safeDistance}))
				{
					// LOG("[%d/%d] Collision happenning => rerolling asteroid\n", i, n);
					continue;
				}
			}
			addObject(asteroid);
			++i;
		}
	}

	Arena::Arena(LevelType &level) : Level{level}
	{
		reset();
	}

	void Arena::handleEvents(const sf::Event &event)
	{
		if (event.type == sf::Event::Closed)
			globals::WINDOW->close();
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			globals::WINDOW->setView(globals::WINDOW->getDefaultView());
			level = LevelType::MENU;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		{
			paused = !paused;
		}
		else
			controledObject->handleEvents(event);
	}

	void Arena::frameUpdate()
	{
		collisionModel.updateCollisions();

		for (auto &aiShip : aiShips)
		{
			if (aiShip->getTeam() == blueTeam)
				aiShip->determineTactic(blueTeamShips, redTeamShips, collidables, projectiles);
			else
				aiShip->determineTactic(redTeamShips, blueTeamShips, collidables, projectiles);
		}
		for (auto &obj : frameUpdateables)
			obj->frameUpdate();

		for (auto &obj : shooters)
		{
			auto proj = obj->shoot();

			if (proj != nullptr)
				addObject(proj);
		}
	}

	void Arena::draw()
	{
		static int draws = 0;
		static int pov = 0;
		draws++;
		draws %= 10000;

		if (draws % 200 == 0)
		{
			++pov;
			pov %= aiShips.size();
		}

		globals::WINDOW->clear(sf::Color::White);

		sf::View v = globals::WINDOW->getView();

		v.setCenter(aiShips[pov]->getSprite().getPosition());

		globals::WINDOW->setView(v);

		// todo dont draw objects outside view
		for (auto &obj : drawables)
		{
			globals::WINDOW->draw(*obj);
		}
		globals::WINDOW->display();
	}

	void Arena::render()
	{
		if (paused)
			return;

		frameUpdate();
		draw();
	}
	Arena::~Arena()
	{
	}

	void Arena::debugPrint()
	{
		printf("drawables %zd, collidables %zd, frameUpd %zd, shooters %zd\n", drawables.size(), collidables.size(), frameUpdateables.size(), shooters.size());
		printf("\n----Arena----\n");
		for (auto &obj : drawables)
		{
			auto proj = std::dynamic_pointer_cast<ships::Projectile>(obj);
			std::string s = "";
			if (proj)
				s = proj->getId();

			auto collid = std::dynamic_pointer_cast<rendering::CollisionObject>(obj);
			if (collid)
				s = collid->getId();
			if (s != "")
				printf("[%s]\n", s.c_str());
		}
		std::cout << std::endl;
	}
} // namespace levels