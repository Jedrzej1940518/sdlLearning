#pragma once

#include "utils.hpp"

namespace physics
{

    enum class DIRECTION
    {
        right = 0,
        down = 90,
        left = 180,
        up = 270
    };
    struct GridCoords
    {
        int row;
        int column;
    };
    struct GridPosition
    {
        int row;
        int column;
        int index;
    };
    struct GridParams
    {
        int mapWidth;
        int mapHeight;
        int cellSide;
    };
    struct CollisionParams
    {
        bool collided;
        sf::Vector2f velocity;
        sf::Vector2f collisionVector;
        float mass;

        CollisionParams() : collided{false}, velocity{0, 0}, collisionVector{0, 0}, mass{0} {}
        CollisionParams(bool collided, sf::Vector2f velocity, sf::Vector2f collisionVector, float mass) : collided{collided}, velocity{velocity}, collisionVector{collisionVector}, mass{mass} {}
    };
    struct Circle
    {
        sf::Vector2f position;
        float radius;
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
    sf::Vector2f calculateSpeed(const sf::Vector2f &velocity, float maxVelocity, float acceleration, float accelerationAngle);
    sf::Vector2f clampVector(const sf::Vector2f &velocity, float maxVelocity);
    float distance(const sf::Vector2f &a, const sf::Vector2f &b);
    float getAngleBetweenPoints(const sf::Vector2f &a, const sf::Vector2f &b);

    bool collisionHappening(const Circle &a, const Circle &b);

    void slowDown(sf::Vector2f &velocity, sf::Vector2f &position, const GridParams &gridParams);
    void printVector(const sf::Vector2f &v);

} // namespace physics