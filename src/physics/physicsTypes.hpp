#pragma once

#include <SFML/System/Vector2.hpp>

namespace physics
{
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

}