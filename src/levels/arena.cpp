#include "arena.hpp"
#include "rendering/background.hpp"
#include "ships/aiShip.hpp"

// #include "prefabs/prefabs.hpp"

namespace levels
{
	void Arena::populateArenaWithAsteroids(int n)
	{
		constexpr int safeDistance = 100;

		auto getRandomAsteroidPrefab = []() -> const prefabs::CollidablePrefab& {
			int r = getRandomNumber(0, 100);
			return (r > 80) ? prefabs::asteroidBig2 : (r > 40) ? prefabs::asteroid2 : prefabs::asteroid3;
			};

		for (int i = 0; i < n;)
		{
			const auto& prefab = getRandomAsteroidPrefab();
			float xx = static_cast<float>(getRandomNumber(-x, x));
			float yy = static_cast<float>(getRandomNumber(-y, y));
			float vX = 0 - xx;//getRandomNumber(-prefab.maxVelocity, prefab.maxVelocity);
			float vY = 0 - yy;//getRandomNumber(-prefab.maxVelocity, prefab.maxVelocity);
			auto asteroid = std::make_shared<rendering::CollisionObject>(prefab, sf::Vector2f{ xx, yy }, sf::Vector2f{ vX, vY });

			for (const auto& obj : collidables) {
				if (physics::collisionHappening(obj->getCollisionCircle(), { {xx,yy}, asteroid->getRadius() + safeDistance }))
				{
					LOG("[%d/%d] Collision happenning => rerolling asteroid\n", i, n);
					continue;
				}
			}
			addObject(asteroid);
			++i;
		}

	}

	Arena::Arena(sf::RenderWindow& window, LevelType& level) : Level{ window, level } //: console{gRenderer, getconsoleRect()}
	{
		auto background = std::make_shared<rendering::Background>(prefabs::background);

		auto wolf = std::make_shared<ships::AiShip>(prefabs::wolf, sf::Vector2f{ -200, -200 });
		auto lasher = std::make_shared<ships::AiShip>(prefabs::lasher, sf::Vector2f{ 200, 0 });

		auto player = std::make_shared<ships::PlayerShip>(prefabs::scarab, sf::Vector2f{ 0, 0 });

		addObject(background);
		addObject(wolf);
		addObject(lasher);
		addObject(player, true);

		int asteroids{ 30 };
		populateArenaWithAsteroids(asteroids);
	}

	void Arena::handleEvents(const sf::Event& event)
	{
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			window.setView(window.getDefaultView());
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

		for (auto& aiShip : aiShips)
			aiShip->determineTactic(hostileShips, playerShips, collidables, projectiles);

		for (auto& obj : frameUpdateables)
			obj->frameUpdate();

		for (auto& obj : shooters)
		{
			auto proj = obj->shoot();

			if (proj != nullptr)
				addObject(proj);
		}
		cleanupDeads();

		sf::View v = window.getView();
		v.setCenter(controledObject->getSprite().getPosition());
		window.setView(v);
	}

	void Arena::draw()
	{
		// todo dont draw objects outside view
		for (auto& obj : drawables)
			window.draw(*obj);
	}

	void Arena::render()
	{
		if (paused)
			return;

		window.clear(sf::Color::White);

		frameUpdate();
		draw();

		window.display();
	}
	Arena::~Arena()
	{
	}

	void Arena::debugPrint()
	{
		printf("drawables %zd, collidables %zd, frameUpd %zd, shooters %zd\n", drawables.size(), collidables.size(), frameUpdateables.size(), shooters.size());
		printf("\n----Arena----\n");
		for (auto& obj : drawables)
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