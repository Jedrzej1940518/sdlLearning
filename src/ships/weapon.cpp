#include "weapon.hpp"

#include <memory>

namespace ships
{

	Weapon::Weapon(const prefabs::ProjectilePrefab &prefab, sf::Vector2f weaponPositionOffset) : prefab{prefab}, weaponPositionOffset{weaponPositionOffset}, shellReload{prefab.reload}
	{
		auto fakeProjectile = std::make_unique<Projectile>(prefab, sf::Vector2f{0, 0}, sf::Vector2f{1, 1}, 30.f);
		projectileRadius = fakeProjectile->getRadius();
	}
	void Weapon::frameUpdate()
	{
		--shellReload;
		shellReload = std::max(shellReload, 0);
	}

	std::shared_ptr<Projectile> Weapon::shoot(float angle, const sf::Vector2f &shooterPos, const sf::Vector2f &shooterSpeed)
	{
		if (shellReload > 0)
			return nullptr;

		float scatter = getRandomNumber(-prefab.scatterAngle, prefab.scatterAngle);
		float shotAngle = angle + scatter;

		sf::Vector2f shotSpawnPoint = getProjectileSpawnPoint(angle, shooterPos);
		sf::Vector2f shotVelocity = getProjectileVelocity(shotAngle) + shooterSpeed;

		shellReload = prefab.reload;

		globals::TIMER->startTimer("shootingMakeShared");

		auto p = std::make_shared<Projectile>(prefab, shotSpawnPoint, shotVelocity, shotAngle);

		globals::TIMER->endTimer("shootingMakeShared");

		return p;
	}

	sf::Vector2f Weapon::getProjectileSpawnPoint(float angle, const sf::Vector2f &shooterPos) const
	{
		sf::Transform t;
		// todo this only works if we spawn proj on top of ships
		auto shotOffset = t.rotate(angle + constants::CARTESIAN_TO_SFML_ANGLE).transformPoint(weaponPositionOffset + sf::Vector2f{0, -projectileRadius - 1.f});
		return shooterPos + shotOffset;
	}
	sf::Vector2f Weapon::getProjectileVelocity(float angle) const
	{
		sf::Vector2f shotVector = physics::getRotatedVector(angle);
		return shotVector * prefab.maxVelocity;
	}
};
