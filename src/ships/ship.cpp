#include "ship.hpp"

namespace ships
{
	Ship::Ship(const prefabs::ShipPrefab &prefab, int team, sf::Vector2f position, sf::Vector2f velocity, float rotation) : CollisionObject{prefab, position, velocity, rotation}, team{team}, weapon{prefab.weaponPrefab, {0, -spriteRadius}}
	{
		static int shipsId = 0;
		shipId = shipsId;
		shipsId++;
		if (shipsId > 100000)
			shipsId = 0;
	}

	void Ship::frameUpdate()
	{
		globals::TIMER->startTimer("ShipFrameUpdate");
		float relativeAngle = physics::normalizeDegrees(targetAngle - getRotationCartesian());
		body.rotateOnce(relativeAngle);
		body.accelerateOnce(accelerationVector);
		weapon.frameUpdate();

		CollisionObject::frameUpdate();

		shapesToDraw.push_back(makeCircle(getCenter(), spriteRadius, team == config::RED_TEAM ? sf::Color::Red : sf::Color::Blue));

		if (config::debugObject)
		{
			sf::Vector2f rotationVector = physics::getRotatedVector(targetAngle);
			auto [arrowBase, arrowPoint] = getVectorShapes(rotationVector, getCenter(), sf::Color::Green, 150.f);
			shapesToDraw.push_back(std::move(arrowBase));
			shapesToDraw.push_back(std::move(arrowPoint));
		}
		globals::TIMER->endTimer("ShipFrameUpdate");
	}

	std::shared_ptr<Projectile> Ship::shoot()
	{
		if (not isShooting)
			return nullptr;

		auto p = weapon.shoot(getRotationCartesian(), getCenter(), getVelocity());

		return p;
	}
}