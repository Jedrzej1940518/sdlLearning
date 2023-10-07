
#include "body.hpp"
#include "physics.hpp"
#include <SDL2/SDL_rect.h>

namespace physics
{
    Body::Body(Hardware hardware) : Body({0.0, 0.0}, 0.0, hardware)
    {
    }

    Body::Body(Vector2d speed, double rotation, Hardware hardware)
        : speed{speed},
          rotation{rotation}, hardware{hardware}, rotationLeft{0}, accelerating{false}
    {
    }

    void Body::handleColision(CollisionParams &cp)
    {
        if (cp.collided)
        {
            auto s = speed * (((hardware.mass) - cp.mass) / (hardware.mass + cp.mass));
            auto s2 = cp.speed * ((cp.mass * 2.) / (hardware.mass + cp.mass));

            speed = s + s2;
            speed = physics::clampVector(speed, hardware.maxSpeed);
            cp.collided = false;
        }
    }
    void Body::frameUpdate(CollisionParams &collisionParams)
    {

        handleColision(collisionParams);
        auto maxRotationSpeed = hardware.maxRotationSpeed;

        if (accelerating)
            speed = calculateSpeed(speed, hardware.maxSpeed, hardware.acceleration, rotation);
        if (abs(rotationLeft) > 0)
        {
            auto rotationTick = std::clamp<double>(rotationLeft, -maxRotationSpeed, maxRotationSpeed);
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
        return hardware.mass;
    }
} // namespace physics