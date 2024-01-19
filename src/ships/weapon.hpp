#pragma once

#include "projectile.hpp"
#include "frameUpdateable.hpp"

#include <memory>

namespace ships
{
	class Weapon : public FrameUpdateable
	{
		const prefabs::ProjectilePrefab& prefab;

		sf::Vector2f weaponPositionOffset;
		int shellReload{ 0 };

	public:
		Weapon(const prefabs::ProjectilePrefab& prefab, sf::Vector2f weaponPositionOffset);
		void frameUpdate() override;
		std::shared_ptr<Projectile> shoot(float angle, const sf::Vector2f& shooterPos);

		//getters
		float getLifetime() const { return prefab.lifetime; }
		float getMaxVelocity() const { return prefab.maxVelocity; }
		sf::Vector2f getProjectileSpawnPoint(float angle, const sf::Vector2f& shooterPos) const;
		sf::Vector2f getProjectileVelocity(float angle) const;
	};
}