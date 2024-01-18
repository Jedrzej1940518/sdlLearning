#pragma once

#include <SFML/System/Vector2.hpp>

namespace physics
{
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

    struct CollisionModelAttributes
    {
        GridPosition gridPosition;
        Circle collisionCircle;
    };

}