#include "projectile.hpp"

namespace ships
{

    Projectile *Projectile::spawnProjectile(const prefabs::ProjectilePrefab &projectilePrefab, const CollisionObject &shooter)
    {
        Vector2d shotAngle = physics::getRotatedVector(shooter.getBody().getRotation());
        Vector2d shotSpawnDistance = shotAngle * -shooter.getHeight();

        return new Projectile(projectilePrefab, shooter.getObjectCenter() + shotSpawnDistance, shotAngle * -10 + shooter.getBody().getSpeed());
    }
    void Projectile::handleCollision(CollisionObject &oth)
    {
        printf("Hit! Dmg = %d\n", projectilePrefab.dmg);
        oth.hit(projectilePrefab.dmg);
        alive = false;
    }

    Projectile::Projectile(const prefabs::ProjectilePrefab &projectilePrefab, physics::Vector2d position, physics::Vector2d speed, double rotation) : CollisionObject(projectilePrefab, position, speed, rotation), projectilePrefab{projectilePrefab}, lifetime{projectilePrefab.lifetime}
    {
        hp = 0;
    }

    Projectile::~Projectile()
    {
    }

    void Projectile::frameUpdate(physics::CollisionModel &collisionModel)
    {
        CollisionObject::frameUpdate(collisionModel);
        --lifetime;
        alive &= lifetime > 0;
    };
}
