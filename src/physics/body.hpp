#pragma once

#include "physics.hpp"
#include <array>

namespace physics
{

class Body
{
    Vector2d speed;
    Vector2d maxSpeed;
    double acceleration;
    std::array<bool, directionNumber> accelerationDirections;

  public:
    Body(Vector2d speed, Vector2d maxSpeed, double acceleration);

    void accelerate(Direction direction);
    void deaccelerate(Direction direction);
    void frameUpdate();

    Vector2d getSpeed() const;

    string printDirections() const;
    void printBody() const;
};
} // namespace physics