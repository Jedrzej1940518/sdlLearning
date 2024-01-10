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

    public:
        Projectile(const prefabs::ProjectilePrefab &projectilePrefab, physics::Vector2d position, physics::Vector2d speed = {0, 0}, double rotation = 0);
        static Projectile *spawnProjectile(const prefabs::ProjectilePrefab &projectilePrefab, const CollisionObject &shooter);
        void frameUpdate(physics::CollisionModel &collisionModel);
        virtual void handleCollision(CollisionObject &oth);
        virtual ~Projectile();
    };

}