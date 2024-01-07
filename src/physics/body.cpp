
#include "body.hpp"
#include "physics.hpp"
#include <SDL2/SDL_rect.h>

namespace physics
{
    Body::Body(Hardware hardware) : Body({0.0, 0.0}, 0.0, hardware)
    {
    }

    Body::Body(Vector2d speed, double rotation, Hardware hardware)
        : bounce{0, 0}, speed{speed},
          rotation{rotation}, hardware{hardware}, rotationLeft{0}, accelerating{false}, accelerationAngle{0}, acceleratingOnce{false}
    {
    }

    void Body::handleColision(CollisionParams &cp)
    {
        if (cp.collided)
        {
            bounce = {-speed.x * 2, -speed.y * 2};
            double v1 = physics::vectorLenght(speed);
            double v2 = physics::vectorLenght(cp.speed);
            double m1 = hardware.mass;
            double m2 = cp.mass * 1;
            double theta1 = physics::getVectorRotationRadians(speed);
            double theta2 = physics::getVectorRotationRadians(cp.speed);
            double phi = theta1 > theta2 ? theta1 - theta2 : theta2 - theta1;

            double v1x = ((v1 * cos(theta1 - phi) * (m1 - m2) + 2 * m2 * v2 * cos(theta2 - phi)) / (m1 + m2)) * cos(phi) + v1 * sin(theta1 - phi) * cos(phi + M_PI / 2.);
            double v1y = ((v1 * cos(theta1 - phi) * (m1 - m2) + 2 * m2 * v2 * cos(theta2 - phi)) / (m1 + m2)) * sin(phi) + v1 * sin(theta1 - phi) * sin(phi + M_PI / 2.);
            Vector2d newSpeed{v1x, v1y};
            rotationLeft = getVectorRotation(newSpeed);
            speed = physics::clampVector(newSpeed, hardware.maxSpeed);
            accelerating = false;
            cp.collided = false;
        }
    }
    void Body::frameUpdate(CollisionParams &collisionParams)
    {

        handleColision(collisionParams);
        auto maxRotationSpeed = hardware.maxRotationSpeed;

        if (abs(rotationLeft) > 0)
        {
            auto rotationTick = std::clamp<double>(rotationLeft, -maxRotationSpeed, maxRotationSpeed);
            rotation += rotationTick;
            rotationLeft -= rotationTick;
        }

        if (accelerating)
            speed = calculateSpeed(speed, hardware.maxSpeed, hardware.acceleration, rotation);

        else if (acceleratingOnce)
        {
            speed = calculateSpeed(speed, hardware.maxSpeed, hardware.acceleration, accelerationAngle);
            acceleratingOnce = false;
        }
    }

    void Body::accelerate()
    {
        acceleratingOnce = false;
        accelerating = true;
    }
    void Body::accelerateOnce(double angle)
    {
        accelerating = false;
        accelerationAngle = angle;
        acceleratingOnce = true;
    }

    void Body::deaccelerate()
    {
        accelerating = false;
    }
    void Body::rotateOnce(DIRECTION rd)
    {
        rotationLeft = (rd == DIRECTION::right ? hardware.maxRotationSpeed : -hardware.maxRotationSpeed);
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
    const Vector2d &Body::getSpeed() const { return speed; }
    Vector2d Body::applyBounce()
    {
        Vector2d bounceToApply = bounce;
        bounce = {0, 0};
        return bounceToApply;
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