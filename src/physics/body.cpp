
#include "body.hpp"
#include "physics.hpp"

namespace physics
{
    Body::Body(float maxRotationSpeed, float maxVelocity, float acceleration, float mass) : Body({0.0, 0.0}, 0.0, maxRotationSpeed, maxVelocity, acceleration, mass)
    {
    }

    Body::Body(sf::Vector2f velocity, float rotation, float maxRotationSpeed, float maxVelocity, float acceleration, float mass)
        : bounce{0, 0}, velocity{velocity}, rotation{rotation},
          maxRotationSpeed{maxRotationSpeed}, maxVelocity{maxVelocity}, acceleration{acceleration}, mass{mass},
          rotationLeft{0}, accelerationAngle{0}, acceleratingOnce{false}
    {
    }

    void Body::consumeCollision(CollisionParams &cp)
    {
        // TODO chceck this
        if (cp.collided)
        {
            bounce = -cp.collisionVector * constants::collisionBounce;
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
            acceleratingOnce = false;
            cp = {};
        }
    }
    void Body::frameUpdate()
    {
        if (abs(rotationLeft) > 0)
        {
            rotation += rotationLeft;
            rotationLeft = 0;
            rotation = physics::normalizeDegrees(rotation);
        }

        if (acceleratingOnce)
        {
            velocity = calculateSpeed(velocity, maxVelocity, acceleration, accelerationAngle);
            acceleratingOnce = false;
        }
    }

    void Body::accelerateOnce(float angle)
    {
        accelerationAngle = angle;
        acceleratingOnce = true;
    }

    void Body::rotateOnce(DIRECTION rd)
    {
        rotationLeft = (rd == DIRECTION::right ? maxRotationSpeed : -maxRotationSpeed);
    }

    void Body::setVelocity(sf::Vector2f v)
    {
        velocity = v;
    }
    void Body::setRotation(float r)
    {
        rotation = r;
    }

    void Body::printBody() const
    {
        printf("Velocity {%f, %f}\n", velocity.x, velocity.y);
    }

    const sf::Vector2f &Body::getVelocity() const { return velocity; }
    sf::Vector2f Body::consumeBounce()
    {
        sf::Vector2f bounceToApply = bounce;
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
    float Body::getMass() const
    {
        return mass;
    }
} // namespace physics