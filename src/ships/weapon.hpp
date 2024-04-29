#pragma once

#include "projectile.hpp"
#include "frameUpdateable.hpp"

#include <memory>

namespace ships
{
	class Weapon : public FrameUpdateable
	{
		const prefabs::ProjectilePrefab &prefab;

		sf::Vector2f weaponPositionOffset;
		int shellReload{0};
		float projectileRadius{0};

	public:
		Weapon(const prefabs::ProjectilePrefab &prefab, sf::Vector2f weaponPositionOffset);
		void frameUpdate() override;
		std::shared_ptr<Projectile> shoot(float angle, const sf::Vector2f &shooterPos, const sf::Vector2f &shooterSpeed);

		// getters
		int getLifetime() const { return prefab.lifetime; }
		int getDmg() const { return prefab.dmg; }
		float getMaxVelocity() const { return prefab.maxVelocity; }
		float getScatter() const { return prefab.scatterAngle; }
		float getProjectileRadius() const { return projectileRadius; }

		float getReload() const { return shellReload; }
		float getMaxReload() const { return prefab.reload; }
		bool canShoot() const { return shellReload <= 0; }

		//
		sf::Vector2f getProjectileSpawnPoint(float angle, const sf::Vector2f &shooterPos) const;
		sf::Vector2f getProjectileVelocity(float angle) const;
	};
}