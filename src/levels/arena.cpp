#include "arena.hpp"
#include "rendering/background.hpp"
#include "ships/aiShip.hpp"

// #include "prefabs/prefabs.hpp"

namespace levels
{

	Arena::StepType Arena::step(ships::Tactic::TacticOutcome tactic)
	{
		neuralNetworkShip->setTactic(tactic);

		int playerTeamHp = 0;
		int enemyTeamHp = 0;

		std::for_each(playerShips.begin(), playerShips.end(), [&playerTeamHp](auto &obj)
					  { playerTeamHp += obj->getHp(); });
		std::for_each(hostileShips.begin(), hostileShips.end(), [&enemyTeamHp](auto &obj)
					  { enemyTeamHp += obj->getHp(); });
		std::cout << "player team hp " << playerTeamHp << " enemy team hp " << enemyTeamHp << std::endl;

		frameUpdate();

		std::for_each(playerShips.begin(), playerShips.end(), [&playerTeamHp](auto &obj)
					  { playerTeamHp -= obj->getHp(); });
		std::for_each(hostileShips.begin(), hostileShips.end(), [&enemyTeamHp](auto &obj)
					  { enemyTeamHp -= obj->getHp(); });

		int reward = enemyTeamHp - playerTeamHp; // how much hp diff we gained
		bool done = neuralNetworkShip->getHp() <= 0;
		std::cout << "delta: player team hp " << playerTeamHp << " enemy team hp " << enemyTeamHp << " reward " << reward << std::endl;

		return std::make_tuple(make_obs(), reward, done);
	}
	Arena::ObservationType Arena::reset()
	{
		clear();

		auto background = std::make_shared<rendering::Background>(prefabs::background);

		auto wolf = std::make_shared<ships::AiShip>(prefabs::wolf, sf::Vector2f{-200, -200});
		auto lasher = std::make_shared<ships::AiShip>(prefabs::lasher, sf::Vector2f{200, 0});

		auto wolf2 = std::make_shared<ships::AiShip>(prefabs::wolf, sf::Vector2f{-400, -200});
		auto lasher2 = std::make_shared<ships::AiShip>(prefabs::lasher, sf::Vector2f{400, 0});
		auto hammerhead = std::make_shared<ships::AiShip>(prefabs::hammerhead, sf::Vector2f{0, -200});

		// auto player = std::make_shared<ships::PlayerShip>(prefabs::scarab, sf::Vector2f{ 0, 0 });
		auto neuralNetwork = std::make_shared<ships::AiShip>(prefabs::scarab, sf::Vector2f{0, 0});

		addObject(background);
		// addObject(wolf);
		addObject(lasher);
		// addObject(wolf2);
		// addObject(lasher2);
		// addObject(hammerhead);

		addObject(neuralNetwork, true);
		neuralNetworkShip = neuralNetwork;

		populateArenaWithAsteroids(asteroids_number);

		return make_obs();
	}
	Arena::ObservationType Arena::make_obs()
	{
		if (hostileShips.size() == 0)
			return ObservationType{};

		auto vel = neuralNetworkShip->getVelocity();
		auto velNormalized = vel / neuralNetworkShip->getMaxVelocity();

		auto relativePos = neuralNetworkShip->getCenter() - hostileShips[0]->getCenter();
		auto rposNorm = relativePos / 10000.f; // damn thats big
		auto hostileVel = hostileShips[0]->getVelocity() / hostileShips[0]->getMaxVelocity();
		auto obs = ObservationType{
			rposNorm.x, rposNorm.y,
			hostileVel.x, hostileVel.y,
			velNormalized.x, velNormalized.y,
			neuralNetworkShip->getRotationCartesian(),
			neuralNetworkShip->getCooldown() / neuralNetworkShip->getMaxCooldown()};

		return obs;
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
			aiShip->determineTactic(hostileShips, playerShips, collidables, projectiles);

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
		sf::View v = globals::WINDOW->getView();
		v.setCenter(controledObject->getSprite().getPosition());
		globals::WINDOW->setView(v);

		// todo dont draw objects outside view
		for (auto &obj : drawables)
			globals::WINDOW->draw(*obj);
	}

	void Arena::render()
	{
		if (paused)
			return;

		globals::WINDOW->clear(sf::Color::White);

		frameUpdate();
		draw();

		globals::WINDOW->display();
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