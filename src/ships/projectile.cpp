#include "projectile.hpp"

namespace ships
{

    void Projectile::handleCollision(CollisionObject &oth)
    {
        printf("Hit! Dmg = %d\n", projectilePrefab.dmg);
        oth.hit(projectilePrefab.dmg);
    }

    Projectile::Projectile(prefabs::ProjectilePrefab &projectilePrefab, physics::Vector2d position, physics::Vector2d speed, double rotation) : CollisionObject(projectilePrefab, position, speed, rotation), projectilePrefab{projectilePrefab}, lifetime{projectilePrefab.lifetime} {}

    Projectile::~Projectile()
    {
    }

    void Projectile::frameUpdate(physics::CollisionModel &collisionModel)
    {
        CollisionObject::frameUpdate(collisionModel);
        --lifetime;
        alive = lifetime > 0;
    };
}
