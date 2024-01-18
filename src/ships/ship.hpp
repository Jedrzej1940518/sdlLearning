#pragma once

#include "weapon.hpp"

#include "rendering/collisionObject.hpp"

namespace ships
{
    class Ship : public rendering::CollisionObject
    {
    protected:
        bool isShooting{false};
        Weapon weapon;

    public:
        Ship(const prefabs::ShipPrefab &prefab, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, float rotation = 0);

        std::shared_ptr<Projectile> shoot()
        {
            if (not isShooting)
                return nullptr;

            return weapon.shoot(getRotationCartesian(), getCenter());
        }
    };
}