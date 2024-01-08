#pragma once

#include "../rendering/collisionObject.hpp"
#include "../physics/physics.hpp"
#include "../physics/collisionModel.hpp"
#include "../prefabs/prefabs.hpp"
#include "projectile.hpp"

namespace ships
{
    class Ship : public rendering::CollisionObject
    {
        bool inputDirections[4];
        bool spawnProjectile;

    public:
        Ship(prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d speed = {0, 0}, double rotation = 0);

        void shoot();

        void addInput(physics::DIRECTION dir);
        void removeInput(physics::DIRECTION dir);

        void rotateLeft();
        void rotateRight();
        void stopRotateLeft();
        void stopRotateRight();

        Projectile *frameUpdate();
    };
}