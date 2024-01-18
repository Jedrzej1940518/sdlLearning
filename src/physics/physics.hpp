#pragma once

#include "utils.hpp"
#include "physicsTypes.hpp"

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

    sf::Vector2f getRotatedVector(float degrees);
    float getVectorRotation(const sf::Vector2f &v);

    sf::Vector2f predictPosition(const sf::Vector2f &pos, const sf::Vector2f &velocity, int ticks);
    int calculateTicks(const sf::Vector2f &offset, float velocity);

    float vectorLenght(const sf::Vector2f &v);
    sf::Vector2f calculateSpeed(const sf::Vector2f &velocity, float maxVelocity, float maxAcceleration, float accelerationAngle);
    sf::Vector2f clampVector(const sf::Vector2f &velocity, float maxVelocity);
    float distance(const sf::Vector2f &a, const sf::Vector2f &b);

    bool collisionHappening(const Circle &a, const Circle &b);

    void slowDown(sf::Vector2f &velocity, sf::Vector2f &position, const GridParams &gridParams);
    void printVector(const sf::Vector2f &v);

} // namespace physics