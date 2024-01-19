#include "weapon.hpp"

#include <memory>

namespace ships
{

	Weapon::Weapon(const prefabs::ProjectilePrefab& prefab, sf::Vector2f weaponPositionOffset) : prefab{ prefab }, weaponPositionOffset{ weaponPositionOffset }, shellReload{ prefab.reload } {}
	void Weapon::frameUpdate() { --shellReload; }

	std::shared_ptr<Projectile> Weapon::shoot(float angle, const sf::Vector2f& shooterPos)
	{
		if (shellReload > 0)
			return nullptr;

		float scatter = getRandomNumber(-prefab.scatterAngle, prefab.scatterAngle);
		float shotAngle = angle + scatter;

		sf::Vector2f shotSpawnPoint = getProjectileSpawnPoint(angle, shooterPos);
		sf::Vector2f shotVelocity = getProjectileVelocity(shotAngle);

		shellReload = prefab.reload;

		return std::make_shared<Projectile>(prefab, shotSpawnPoint, shotVelocity, shotAngle);
	}

	sf::Vector2f Weapon::getProjectileSpawnPoint(float angle, const sf::Vector2f& shooterPos) const
	{
		sf::Transform vecRotation;
		vecRotation.rotate(angle + constants::CARTESIAN_TO_SFML_ANGLE);
		auto shotOffset = vecRotation.transformPoint(weaponPositionOffset);
		return shooterPos + shotOffset;

	}
	sf::Vector2f Weapon::getProjectileVelocity(float angle) const
	{
		sf::Vector2f shotVector = physics::getRotatedVector(angle);
		return shotVector * prefab.maxVelocity;
	}
};
