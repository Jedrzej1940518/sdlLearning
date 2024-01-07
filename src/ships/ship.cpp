
#include "ship.hpp"

namespace ships
{
    Ship::Ship(prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d speed,
               double rotation) : CollisionObject{prefab, position, speed, rotation} {}

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

    void Ship::frameUpdate()
    {
        bool accelerateOnce = false;

        for (int i = 0; i < 4; ++i)
        {
            accelerateOnce |= inputDirections[i];
        }

        if (accelerateOnce)
            body.accelerateOnce(physics::sumDirections(inputDirections));
    }
}