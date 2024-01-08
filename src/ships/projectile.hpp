#pragma once

#include "../rendering/collisionObject.hpp"
#include "../physics/physics.hpp"
#include "../physics/collisionModel.hpp"
#include "../prefabs/prefabs.hpp"

namespace ships
{
    class Projectile : public rendering::CollisionObject
    {
        const prefabs::ProjectilePrefab &projectilePrefab;
        int lifetime;
        bool alive{true};

    public:
        Projectile(prefabs::ProjectilePrefab &projectilePrefab, physics::Vector2d position, physics::Vector2d speed = {0, 0}, double rotation = 0);
        void frameUpdate(physics::CollisionModel &collisionModel);
        virtual void handleCollision(CollisionObject &oth);
        bool isAlive() const { return alive; }
        virtual ~Projectile();
    };

}