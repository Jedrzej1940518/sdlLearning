
#include "body.hpp"
#include "physics.hpp"
#include <SDL2/SDL_rect.h>

namespace physics
{
    Body::Body(Hardware hardware) : Body({0.0, 0.0}, 0.0, hardware)
    {
    }

    Body::Body(Vector2d velocity, double rotation, Hardware hardware)
        : bounce{0, 0}, velocity{velocity},
          rotation{rotation}, hardware{hardware}, rotationLeft{0}, accelerating{false}, accelerationAngle{0}, acceleratingOnce{false}
    {
    }

    void Body::handleColision(CollisionParams &cp)
    {
        if (cp.collided)
        {
            bounce = {-velocity.x * 2, -velocity.y * 2};
            double v1 = physics::vectorLenght(velocity);
            double v2 = physics::vectorLenght(cp.velocity);
            double m1 = hardware.mass;
            double m2 = cp.mass * 1;
            double theta1 = physics::getVectorRotationRadians(velocity);
            double theta2 = physics::getVectorRotationRadians(cp.velocity);
            double phi = theta1 > theta2 ? theta1 - theta2 : theta2 - theta1;

            double v1x = ((v1 * cos(theta1 - phi) * (m1 - m2) + 2 * m2 * v2 * cos(theta2 - phi)) / (m1 + m2)) * cos(phi) + v1 * sin(theta1 - phi) * cos(phi + M_PI / 2.);
            double v1y = ((v1 * cos(theta1 - phi) * (m1 - m2) + 2 * m2 * v2 * cos(theta2 - phi)) / (m1 + m2)) * sin(phi) + v1 * sin(theta1 - phi) * sin(phi + M_PI / 2.);
            Vector2d newSpeed{v1x, v1y};
            rotationLeft = getVectorRotation(newSpeed);
            velocity = physics::clampVector(newSpeed, hardware.maxVelocity);
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
            rotation = rotation < 0 ? rotation + 360 : rotation;
            rotation = rotation > 360 ? rotation - 360 : rotation;
        }

        if (accelerating)
            velocity = calculateSpeed(velocity, hardware.maxVelocity, hardware.acceleration, rotation);

        else if (acceleratingOnce)
        {
            velocity = calculateSpeed(velocity, hardware.maxVelocity, hardware.acceleration, accelerationAngle);
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
        printf("Velocity {%f, %f}\n", velocity.x, velocity.y);
    }
    Vector2d &Body::getSpeed()
    {
        return velocity;
    }
    const Vector2d &Body::getSpeed() const { return velocity; }
    Vector2d Body::applyBounce()
    {
        Vector2d bounceToApply = bounce;
        bounce = {0, 0};
        return bounceToApply;
    }
    double Body::getAccelerationAngle() const
    {
        return accelerationAngle;
    }
    double Body::getRotation() const
    {
        return rotation;
    }
    double Body::getRotationLeft()
    {
        return rotationLeft;
    }
    double Body::getMass() const
    {
        return hardware.mass;
    }
} // namespace physics