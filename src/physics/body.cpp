
#include "body.hpp"
#include "physics.hpp"

namespace physics
{
    Body::Body(float maxRotationSpeed, float maxVelocity, float maxAcceleration, float mass) : maxRotationSpeed{maxRotationSpeed}, maxVelocity{maxVelocity}, maxAcceleration{maxAcceleration}, mass{mass}
    {
    }

    void Body::applyCollision(const CollisionParams &cp)
    {
        sf::Vector2f bounce = -cp.collisionVector * constants::COLLISION_BOUNCE;
        position += bounce;

        float v1 = vectorLenght(velocity);
        float v2 = vectorLenght(cp.velocity);
        float m1 = mass;
        float m2 = cp.mass;
        float theta1 = degreesToRadians(getVectorRotation(velocity));
        float theta2 = degreesToRadians(getVectorRotation(cp.velocity));
        float phi = theta1 > theta2 ? theta1 - theta2 : theta2 - theta1;

        float v1x = (float)(((v1 * cos(theta1 - phi) * (m1 - m2) + 2 * m2 * v2 * cos(theta2 - phi)) / (m1 + m2)) * cos(phi) + v1 * sin(theta1 - phi) * cos(phi + M_PI / 2.));
        float v1y = (float)(((v1 * cos(theta1 - phi) * (m1 - m2) + 2 * m2 * v2 * cos(theta2 - phi)) / (m1 + m2)) * sin(phi) + v1 * sin(theta1 - phi) * sin(phi + M_PI / 2.));
        sf::Vector2f newSpeed{v1x, v1y};
        rotationLeft = getVectorRotation(newSpeed); // todo fix this
        velocity = clampVector(newSpeed, maxVelocity);
    }
    void Body::frameUpdate()
    {
        if (abs(rotationLeft) > 0.1f)
        {
            rotation += rotationLeft;
            rotationLeft = 0;
            rotation = physics::normalizeDegrees(rotation);
        }

        if (acceleratingOnce)
        {
            velocity = calculateSpeed(velocity, maxVelocity, maxAcceleration, accelerationAngle);
            acceleratingOnce = false;
        }
        position += velocity;
    }

    void Body::accelerateOnce(float angle)
    {
        accelerationAngle = angle;
        acceleratingOnce = true;
    }

    void Body::rotateOnce(float degrees)
    {
        rotationLeft = std::clamp(degrees, -maxRotationSpeed, maxRotationSpeed);
    }

} // namespace physics