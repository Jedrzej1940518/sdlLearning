#include "physics.hpp"

#include <algorithm>
#include <cmath>

namespace physics
{
    float degreesToRadians(float degrees)
    {
        return static_cast<float>(degrees * M_PI / 180.);
    }
    float radiansToDegrees(float radians)
    {
        return static_cast<float>(radians * 180. / M_PI);
    }
    float normalizeDegrees(float degrees)
    {
        degrees = fmod(degrees, 360.0f);
        return degrees > 180.f ? degrees - 360 : degrees;
    }

    sf::Vector2f getRotatedVector(float degrees)
    {
        float radians = degreesToRadians(degrees);
        float x = cos(radians);
        float y = sin(radians);
        return {x, y};
    }
    float getVectorRotation(const sf::Vector2f &v)
    {
        float degrees = radiansToDegrees(atan2(v.y, v.x));
        return degrees;
    }
    float getAngleBetweenVectors(const sf::Vector2f &a, const sf::Vector2f &b)
    {
        return normalizeDegrees(getVectorRotation(a) - getVectorRotation(b));
    }
    float getRelativeAngle(const sf::Vector2f &a, const sf::Vector2f &b, float currentAngle)
    {
        sf::Vector2f targetOffset = a - b;
        sf::Vector2f currentRotationVector = physics::getRotatedVector(currentAngle);

        return physics::getAngleBetweenVectors(currentRotationVector, targetOffset);
    }

    sf::Vector2f calculateSpeed(const sf::Vector2f &velocity, float maxVelocity, const sf::Vector2f &acceleration)
    {
        sf::Vector2f newSpeed = velocity + acceleration;
        newSpeed = clampVector(newSpeed, maxVelocity);

        return newSpeed;
    }
    float vectorLenght(const sf::Vector2f &v)
    {
        return sqrt(v.x * v.x + v.y * v.y);
    }
    float getBrakingDistance(float velocity, float acceleration)
    {
        float dist = velocity * velocity / (2.f * acceleration);
        return dist;
    }
    sf::Vector2f clampVector(const sf::Vector2f &velocity, float maxVelocity)
    {
        float scalingFactor = (float)(maxVelocity / vectorLenght(velocity));
        if (scalingFactor > 1)
            return velocity;
        else
            return velocity * scalingFactor;
    }
    sf::Vector2f predictPosition(const sf::Vector2f &pos, const sf::Vector2f &velocity, int ticks)
    {
        return pos + velocity * (float)ticks;
    }
    int calculateTicks(const sf::Vector2f &offset, float velocity)
    {
        return static_cast<int>(vectorLenght(offset) / velocity);
    }

    float sumDirections(bool directions[4])
    {
        sf::Vector2f summedVector{0, 0};

        for (int i = 0; i < 4; ++i)
            if (directions[i])
                summedVector += getRotatedVector(90.f * i);

        return getVectorRotation(summedVector);
    }

    void printVector(const sf::Vector2f &v)
    {
        printf("[%f,%f]\n", v.x, v.y);
    }

    float distance(const sf::Vector2f &a, const sf::Vector2f &b)
    {
        return static_cast<float>(std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2)));
    }

    bool collisionHappening(const Circle &a, const Circle &b)
    {
        auto dist = distance(a.position, b.position);
        return dist < a.radius + b.radius;
    }
} // namespace physics