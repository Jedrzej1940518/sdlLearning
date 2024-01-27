#pragma once

#include "utils.hpp"
#include "physicsTypes.hpp"

#include <optional>

namespace physics
{

    enum class DIRECTION
    {
        right = 0,
        down = 90,
        left = 180,
        up = 270
    };

    float degreesToRadians(float degrees);
    float radiansToDegrees(float radians);
    float normalizeDegrees(float degrees);

    float sumDirections(bool directions[4]);
    float getBrakingDistance(float velocity, float acceleration);

    sf::Vector2f getRotatedVector(float degrees);
    float getVectorRotation(const sf::Vector2f &v);
    float getAngleBetweenVectors(const sf::Vector2f &a, const sf::Vector2f &b);
    float getRelativeAngle(const sf::Vector2f &a, const sf::Vector2f &b, float currentAngle);
    float getVectorMagnitude(const sf::Vector2f &v);
    float getVectorsDotProduct(const sf::Vector2f& a, const sf::Vector2f& b);

    std::optional<sf::Vector2f> getIntersectPosition(const sf::Vector2f& velocityA, const sf::Vector2f& velocityB, const sf::Vector2f& posA, const sf::Vector2f& posB);

    sf::Vector2f predictPosition(const sf::Vector2f &pos, const sf::Vector2f &velocity, int ticks);
    int calculateTicks(const sf::Vector2f &offset, float velocity);

    sf::Vector2f calculateSpeed(const sf::Vector2f &velocity, float maxVelocity, const sf::Vector2f &acceleration);

    sf::Vector2f clampVector(const sf::Vector2f &velocity, float maxVelocity);
    float distance(const sf::Vector2f &a, const sf::Vector2f &b);
    float distance(const Circle& a, const Circle& b);
    float distance(const sf::Vector2f& a, const Circle& b);

    bool collisionHappening(const Circle &a, const Circle &b);
    
    bool isZero(float a);

} // namespace physics