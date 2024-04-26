#include "ship.hpp"

namespace ships
{
	Ship::Ship(const prefabs::ShipPrefab &prefab, sf::Vector2f position, sf::Vector2f velocity, float rotation) : CollisionObject{prefab, position, velocity, rotation}, weapon{prefab.weaponPrefab, {0, -spriteRadius}} {}

	void Ship::frameUpdate()
	{
		float relativeAngle = physics::normalizeDegrees(targetAngle - getRotationCartesian());
		body.rotateOnce(relativeAngle);
		body.accelerateOnce(accelerationVector);
		weapon.frameUpdate();

		CollisionObject::frameUpdate();

		if (config::debugObject)
		{
			sf::Vector2f rotationVector = physics::getRotatedVector(targetAngle);
			auto [arrowBase, arrowPoint] = getVectorShapes(rotationVector, getCenter(), sf::Color::Green, 150.f);
			shapesToDraw.push_back(std::move(arrowBase));
			shapesToDraw.push_back(std::move(arrowPoint));
		}
	}

	std::shared_ptr<Projectile> Ship::shoot()
	{
		if (not isShooting)
			return nullptr;

		auto p = weapon.shoot(getRotationCartesian(), getCenter(), getVelocity());

		return p;
	}
}