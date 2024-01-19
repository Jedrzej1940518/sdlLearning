#include "ship.hpp"

namespace ships
{
	Ship::Ship(const prefabs::ShipPrefab& prefab, sf::Vector2f position, sf::Vector2f velocity, float rotation) : CollisionObject{ prefab, position, velocity, rotation }, weapon{ prefab.weaponPrefab, {0, -spriteRadius - 10} } {}

	void Ship::frameUpdate()
	{
		float relativeAngle = physics::normalizeDegrees(targetAngle - getRotationCartesian());
		body.rotateOnce(relativeAngle);
		body.accelerateOnce(accelerationVector);
		weapon.frameUpdate();

		CollisionObject::frameUpdate();
	}

	std::shared_ptr<Projectile> Ship::shoot()
	{
		if (not isShooting)
			return nullptr;

		return weapon.shoot(getRotationCartesian(), getCenter());
	}
}