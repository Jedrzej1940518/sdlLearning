#pragma once

#include "physics.hpp"
#include <array>

namespace physics
{

class Body
{
    uint mass;
    Vector2d speed;
    Vector2d maxSpeed;
    double acceleration;
    std::array<bool, directionNumber> accelerationDirections;

  public:
    Body(uint mass, Vector2d speed, Vector2d maxSpeed, double acceleration);

    void accelerate(Direction direction);
    void deaccelerate(Direction direction);

    void handleColision(CollisionParams &collisionParams);
    void frameUpdate(CollisionParams &collisionParams);

    Vector2d &getSpeed();
    uint getMass();

    string printDirections() const;
    void printBody() const;
};
} // namespace physics