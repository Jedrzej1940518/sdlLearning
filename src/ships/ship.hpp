#pragma once

#include "weapon.hpp"

#include "rendering/collisionObject.hpp"

namespace ships
{
	class Ship : public rendering::CollisionObject
	{
	protected:
		bool isShooting{false};

		float targetAngle{0.f};					   // ship rotates towards this
		sf::Vector2f accelerationVector{0.f, 0.f}; // ship accelerates in this direction
		Weapon weapon;

	public:
		Ship(const prefabs::ShipPrefab &prefab, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, float rotation = 0);
		void frameUpdate() override;
		std::shared_ptr<Projectile> shoot();

		// todo probably calculate it in a smart way
		float getRange() const { return weapon.getLifetime() * weapon.getMaxVelocity(); }
		float getTargetAngle() const { return targetAngle; }
		float getCooldown() const { return weapon.getReload(); }
		float getMaxCooldown() const { return weapon.getMaxReload(); }

		const Weapon &getWeapon() const { return weapon; }

		virtual ~Ship() {}
	};
}