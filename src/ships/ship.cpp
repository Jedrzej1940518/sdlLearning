
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

    void Ship::rotateLeft()
    {
        body.rotateOnce(physics::DIRECTION::left);
    }

    void Ship::rotateRight()
    {
        body.rotateOnce(physics::DIRECTION::right);
    }

    void Ship::frameUpdate()
    {
        bool accelerateOnce = false;
        double accelerationAngle = physics::sumDirections(inputDirections);
        for (int i = 0; i < 4; ++i)
        {
            accelerateOnce |= inputDirections[i];
            inputDirections[i] = false;
        }

        if (accelerateOnce)
            body.accelerateOnce(accelerationAngle);
    }
}