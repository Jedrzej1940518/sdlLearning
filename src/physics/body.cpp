
#include "body.hpp"
#include "physics.hpp"
#include <SDL2/SDL_rect.h>

namespace physics
{

Body::Body(uint mass, Vector2d speed, Vector2d maxSpeed, double acceleration)
    : mass{mass}, speed{speed}, maxSpeed{maxSpeed}, acceleration{acceleration}
{
    for (auto &b : accelerationDirections)
        b = false;
}

void Body::handleColision(CollisionParams &cp)
{
    if (cp.collided)
    {
        auto s = speed * ((static_cast<double>(mass) - cp.mass) / (static_cast<double>(mass) + cp.mass));
        auto s2 = cp.speed * ((cp.mass * 2.) / (static_cast<double>(mass) + cp.mass));

        speed = s + s2;
        speed = physics::clampVector(speed, maxSpeed);
        cp.collided = false;
    }
}

void Body::frameUpdate(CollisionParams &collisionParams)
{
    handleColision(collisionParams);

    for (int i = 0; i < directionNumber; ++i)
    {
        if (accelerationDirections[i])
        {
            Direction dir = static_cast<Direction>(i);
            speed = calculateSpeed(speed, maxSpeed, acceleration, dir);
        }
    }
}
void Body::accelerate(Direction direction)
{
    accelerationDirections[static_cast<int>(direction)] = true;
}
void Body::deaccelerate(Direction direction)
{
    accelerationDirections[static_cast<int>(direction)] = false;
}

std::string Body::printDirections() const
{
    string s{"Directions "};
    for (int i = 0; i < directionNumber; ++i)
    {
        s += directionToString(static_cast<Direction>(i));
        s += ": ";
        s += boolToString(accelerationDirections[i]);
        s += ", ";
    }
    return s;
}
void Body::printBody() const
{
    printf("Speed {%f, %f}, %s\n", speed.x, speed.y, printDirections().c_str());
}
Vector2d &Body::getSpeed()
{
    return speed;
}
uint Body::getMass()
{
    return mass;
}
} // namespace physics