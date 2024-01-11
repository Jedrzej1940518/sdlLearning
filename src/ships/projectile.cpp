#include "projectile.hpp"
#include "soundManager.hpp"

namespace ships
{

    Projectile *Projectile::spawnProjectile(const prefabs::ProjectilePrefab &projectilePrefab, const CollisionObject &shooter)
    {
        int scatter = getRandomNumber(-projectilePrefab.scatterAngle, projectilePrefab.scatterAngle);
        Vector2d shotAngle = physics::getRotatedVector(shooter.getBody().getRotation() + scatter);
        Vector2d shotSpawnDistance = shotAngle * -shooter.getHeight();
        Vector2d shotVelocity = shotAngle * -projectilePrefab.hardware.maxVelocity; // + shooter.getBody().getSpeed();

        return new Projectile(projectilePrefab, shooter.getObjectCenter() + shotSpawnDistance, shotVelocity);
    }
    void Projectile::handleCollision(CollisionObject &oth)
    {
        if (oth.getMass() == 0)
            return;
        auto sound = projectilePrefab.dmg > 6 ? Sound::SHELL_HIT_BIG : Sound::SHELL_HIT_SMALL;
        soundsToPlay.insert(sound);
        playSounds();
        oth.hit(projectilePrefab.dmg);
        alive = false;
    }

    Projectile::Projectile(const prefabs::ProjectilePrefab &projectilePrefab, physics::Vector2d position, physics::Vector2d velocity, double rotation) : CollisionObject(projectilePrefab, position, velocity, rotation), projectilePrefab{projectilePrefab}, lifetime{projectilePrefab.lifetime}
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
