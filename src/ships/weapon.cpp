#include "weapon.hpp"

#include <memory>

namespace ships
{

    Weapon::Weapon(const prefabs::ProjectilePrefab &prefab, sf::Vector2f weaponPositionOffset) : prefab{prefab}, weaponPositionOffset{weaponPositionOffset}, shellReload{prefab.reload} {}
    void Weapon::frameUpdate() { --shellReload; }

    std::shared_ptr<Projectile> Weapon::shoot(float angle, const sf::Vector2f &shooterPos)
    {
        if (shellReload > 0)
            return nullptr;

        float scatter = getRandomNumber(-prefab.scatterAngle, prefab.scatterAngle);
        float shotAngle = angle + scatter;
        sf::Vector2f shotVector = physics::getRotatedVector(shotAngle);

        sf::Transform vecRotation;
        vecRotation.rotate(angle + constants::CARTESIAN_TO_SFML_ANGLE);
        auto shotOffset = vecRotation.transformPoint(weaponPositionOffset);

        sf::Vector2f shotSpawnPoint = shooterPos + shotOffset;
        sf::Vector2f shotVelocity = shotVector * prefab.maxVelocity;

        shellReload = prefab.reload;

        return std::make_shared<Projectile>(prefab, shotSpawnPoint, shotVelocity, shotAngle);
    }
};
