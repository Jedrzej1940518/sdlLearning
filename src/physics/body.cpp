
#include "body.hpp"
#include "physics.hpp"
#include <SDL2/SDL_rect.h>

namespace physics
{

    Body::Body(uint mass, Vector2d speed, double maxSpeed, double acceleration, double rotation)
        : mass{mass}, speed{speed}, maxSpeed{maxSpeed}, acceleration{acceleration}, rotation{rotation}, accelerating{false}
    {
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

        if (accelerating)
            speed = calculateSpeed(speed, maxSpeed, acceleration, rotation);
    }

    void Body::accelerate()
    {
        accelerating = true;
    }
    void Body::deaccelerate()
    {
        accelerating = false;
    }
    void Body::rotate(double degrees)
    {
        rotation += degrees;
    }

    void Body::printBody() const
    {
        printf("Speed {%f, %f}\n", speed.x, speed.y);
    }
    Vector2d &Body::getSpeed()
    {
        return speed;
    }
    double Body::getRotation()
    {
        return rotation;
    }
    uint Body::getMass()
    {
        return mass;
    }
} // namespace physics