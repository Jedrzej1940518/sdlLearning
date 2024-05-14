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

	auto getHps(const std::vector<std::shared_ptr<ships::AiShip>> &ships)
	{
		int blueTeamHps = 0;
		int redTeamHps = 0;

		for (const auto &ship : ships)
		{
			blueTeamHps += ship->getTeam() == config::BLUE_TEAM ? ship->getHp() : 0;
			redTeamHps += ship->getTeam() == config::RED_TEAM ? ship->getHp() : 0;
		}
		return std::tuple(blueTeamHps, redTeamHps);
	}

	auto teamsHpDelta(int blueTeamPrevHp, int redTeamPrevHp, const std::vector<std::shared_ptr<ships::AiShip>> &ships)
	{
		auto [blueTeamHp, redTeamHp] = getHps(ships);
		return std::tuple(blueTeamHp - blueTeamPrevHp, redTeamHp - redTeamPrevHp);
	}

	Arena::StepType Arena::step(const Tactic &tactic, int frameSkip)
	{
		neuralNetworkShip->setTactic(tactic);

		auto [blueTeamHp, redTeamHp] = getHps(aiShips);

		int blueTeamSize = blueTeamShips.size();
		int redTeamSize = redTeamShips.size();

		for (int i = 0; i < frameSkip; ++i)
		{
			frameUpdate();

			if (recordVideo)
				recordFrame();
		}
		int blueTeamShipsLost = blueTeamSize - blueTeamShips.size();
		int redTeamShipsLost = redTeamSize - redTeamShips.size();

		int team = neuralNetworkShip->getTeam();

		auto [blueTeamHpDelta, redTeamHpDelta] = teamsHpDelta(blueTeamHp, redTeamHp, aiShips);

		float reward = team == blueTeam ? redTeamShipsLost - blueTeamShipsLost : blueTeamShipsLost - redTeamShipsLost;
		reward *= config::SHIP_LOST_REWARD;
		reward += team == blueTeam ? blueTeamHpDelta - redTeamHpDelta : redTeamHpDelta - blueTeamHpDelta;

		bool done = neuralNetworkShip->getHp() <= 0 or (redTeamShips.size() == 0) or (blueTeamShips.size() == 0);
		return std::make_tuple(make_obs(), reward, done);
	}

	void Arena::initScenario0()
	{
		clear();

		std::mt19937 rng(time(nullptr));
		std::uniform_int_distribution<int> coordDistribution(-400, 400);

		addObject(std::make_shared<rendering::Background>(prefabs::background));

		addObject(std::make_shared<ships::AiShip>(prefabs::hammerhead, redTeam, sf::Vector2f{0, 600 + (float)(coordDistribution(rng))}));
		addObject(std::make_shared<ships::AiShip>(prefabs::lasher, blueTeam, sf::Vector2f{0, -300}));

		aiShips.back()->setNeuralNetwork(true);
		neuralNetworkShip = aiShips.back();
	}

	void Arena::initScenario1()
	{
		clear();

		std::mt19937 rng(time(nullptr));
		std::uniform_int_distribution<int> coordDistribution(-400, 400);

		addObject(std::make_shared<rendering::Background>(prefabs::background));

		addObject(std::make_shared<ships::AiShip>(prefabs::hammerhead, redTeam, sf::Vector2f{0, 600 + (float)(coordDistribution(rng))}));
		addObject(std::make_shared<ships::AiShip>(prefabs::scarab, redTeam, sf::Vector2f{800, (float)(coordDistribution(rng))}));
		addObject(std::make_shared<ships::AiShip>(prefabs::scarab, redTeam, sf::Vector2f{-800, (float)(coordDistribution(rng))}));

		addObject(std::make_shared<ships::AiShip>(prefabs::lasher, blueTeam, sf::Vector2f{0, -300}));

		aiShips.back()->setNeuralNetwork(true);
		neuralNetworkShip = aiShips.back();
	}

	void Arena::initScenario2()
	{
		clear();

		std::mt19937 rng(time(nullptr));
		std::uniform_int_distribution<int> coordDistribution(-400, 400);

		addObject(std::make_shared<rendering::Background>(prefabs::background));

		addObject(std::make_shared<ships::AiShip>(prefabs::hammerhead, redTeam, sf::Vector2f{0, 600 + (float)(coordDistribution(rng))}));
		addObject(std::make_shared<ships::AiShip>(prefabs::scarab, redTeam, sf::Vector2f{800, (float)(coordDistribution(rng))}));
		addObject(std::make_shared<ships::AiShip>(prefabs::scarab, redTeam, sf::Vector2f{-800, (float)(coordDistribution(rng))}));

		addObject(std::make_shared<ships::AiShip>(prefabs::hammerhead, blueTeam, sf::Vector2f{0, 0}));
		addObject(std::make_shared<ships::AiShip>(prefabs::lasher, blueTeam, sf::Vector2f{0, -300}));

		aiShips.back()->setNeuralNetwork(true);
		neuralNetworkShip = aiShips.back();
	}

	void Arena::initArena()
	{

		switch (currentScenario)
		{
		case 0:
			initScenario0();
			break;
		case 1:
			initScenario1();
			break;
		case 2:
			initScenario2();
			break;

		default:
			break;
		}

		// populateArenaWithAsteroids(asteroids_number);
	}
	Arena::ObservationType Arena::reset(int scenario, bool recordEpisode)
	{
		currentScenario = scenario;

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
			std::string dirName = "Trainings/Starships/scenario_" + std::to_string(scenario) + "/videos/";
			std::string fileName = dirName + "output_" + std::to_string(episodeNumber) + ".avi";
			videoWriter = std::make_shared<cv::VideoWriter>(fileName, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 60, cv::Size(config::SCREEN_WIDTH, config::SCREEN_HEIGHT));
			std::cout << "Recording episode....Opening writer success? " << videoWriter->isOpened() << std::endl;
		}

		initArena();

		return make_obs();
	}
	Arena::ObservationType Arena::make_obs()
	{
		ObservationFactory obsFactory(currentScenario);
		return obsFactory.makeObservation(*neuralNetworkShip, aiShips);
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
		{
			controledObject->handleEvents(event);
		}
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
		cleanupDeads();
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
		}

		globals::WINDOW->clear(sf::Color::White);

		sf::View v = globals::WINDOW->getView();

		if (aiShips.size() != 0)
		{
			pov %= aiShips.size();
			v.setCenter(aiShips[pov]->getSprite().getPosition());
		}

		globals::WINDOW->setView(v);

		// todo dont draw objects outside view
		for (auto &obj : drawables)
		{
			globals::WINDOW->draw(*obj);
		}
		// globals::WINDOW->display();
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