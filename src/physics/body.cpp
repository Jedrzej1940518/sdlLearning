
#include "body.hpp"
#include "physics.hpp"
#include <SDL2/SDL_rect.h>

namespace physics
{

    Body::Body(uint mass, Vector2d speed, double maxSpeed, double acceleration, double rotationSpeed, double rotation)
        : mass{mass}, speed{speed}, maxSpeed{maxSpeed}, acceleration{acceleration}, rotationSpeed{
                                                                                        rotationSpeed},
          rotation{rotation}, rotationLeft{0}, accelerating{false}
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
        if (abs(rotationLeft) > 0)
        {
            auto rotationTick = std::clamp<double>(rotationLeft, -rotationSpeed, rotationSpeed);
            rotation += rotationTick;
            rotationLeft -= rotationTick;
        }
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
        rotationLeft = degrees;
    }

    void Body::printBody() const
    {
        printf("Speed {%f, %f}\n", speed.x, speed.y);
    }
    Vector2d &Body::getSpeed()
    {
        return speed;
    }
    const Vector2d &Body::getSpeed() const
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