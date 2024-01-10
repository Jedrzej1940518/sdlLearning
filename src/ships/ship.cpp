
#include "ship.hpp"

namespace ships
{
    Ship::Ship(prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d speed,
               double rotation) : CollisionObject{prefab, position, speed, rotation}
    {
        spawnProjectile = false;
        for (int i = 0; i < 4; ++i)
        {
            inputDirections[i] = false;
        }
    }

    void Ship::addInput(physics::DIRECTION dir)
    {
        double angle = static_cast<double>(dir);
        int indx = angle / 90.;
        inputDirections[indx] = true;
    }
    void Ship::removeInput(physics::DIRECTION dir)
    {
        double angle = static_cast<double>(dir);
        int indx = angle / 90.;
        inputDirections[indx] = false;
    }

    void Ship::shoot()
    {
        spawnProjectile = true;
    }

    void Ship::rotateLeft()
    {
        body.rotate(-360);
    }

    void Ship::rotateRight()
    {
        body.rotate(360);
    }
    void Ship::stopRotateLeft()
    {
        body.rotate(0);
    }

    void Ship::stopRotateRight()
    {
        body.rotate(0);
    }

    Projectile *Ship::frameUpdate(CollisionModel &collisionModel)
    {
        CollisionObject::frameUpdate(collisionModel);

        bool accelerateOnce = false;

        for (int i = 0; i < 4; ++i)
        {
            accelerateOnce |= inputDirections[i];
        }

        if (accelerateOnce)
            body.accelerateOnce(physics::sumDirections(inputDirections));

        Projectile *projectile = nullptr;
        if (spawnProjectile)
        {
            projectile = Projectile::spawnProjectile(prefabs::shell, *this);
            spawnProjectile = false;
        }

        return projectile;
    }
}