
#include "playerShip.hpp"
// #include "soundManager.hpp"

namespace ships
{
	PlayerShip::PlayerShip(const prefabs::ShipPrefab& prefab, sf::Vector2f position, sf::Vector2f velocity,
		float rotation) : Ship{ prefab, position, velocity, rotation }
	{
		for (int i = 0; i < 4; ++i)
		{
			inputDirections[i] = false;
		}
	}

	void PlayerShip::handleEvents(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseMoved)
		{
			auto [x, y] = event.mouseMove;
			sf::Vector2f mousePos{ (float)x, (float)y };
			sf::Vector2f screenCenter{ (float)config::SCREEN_WIDTH / 2.f, (float)config::SCREEN_HEIGHT / 2.f };
			sf::Vector2f relativePos = mousePos - screenCenter;
			float neededAngle = physics::getVectorRotation(relativePos);
			targetAngle = neededAngle;
		}
		else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			bool pressed = (event.type == sf::Event::KeyPressed);

			switch (event.key.code)
			{
			case sf::Keyboard::A:
				handleInput(physics::DIRECTION::left, pressed);
				break;
			case sf::Keyboard::D:
				handleInput(physics::DIRECTION::right, pressed);
				break;
			case sf::Keyboard::W:
				handleInput(physics::DIRECTION::up, pressed);
				break;
			case sf::Keyboard::S:
				handleInput(physics::DIRECTION::down, pressed);
				break;
			default:
				break;
			}
		}
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			isShooting = true;

		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			isShooting = false;
	}

	void PlayerShip::handleInput(physics::DIRECTION dir, bool pressed)
	{
		float angle = static_cast<float>(dir);
		int indx = static_cast<int>(angle / 90.);
		inputDirections[indx] = pressed;
	}

	void PlayerShip::frameUpdate()
	{
		bool accelerateOnce = false;

		for (int i = 0; i < 4; ++i)
			accelerateOnce |= inputDirections[i];

		if (accelerateOnce)
			accelerationVector = physics::getRotatedVector(physics::sumDirections(inputDirections)) * getMaxAcceleration();
		else
			accelerationVector = { 0, 0 };

		Ship::frameUpdate();
	}
}