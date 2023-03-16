#pragma once

#include "physics.hpp"
#include <array>

namespace physics
{

class Body
{
    Vector2d position;
    Vector2d speed;
    Vector2d maxSpeed;
    double acceleration;
    std::array<bool, directionNumber> accelerationDirections;

  public:
    Body(Vector2d position, Vector2d speed, Vector2d maxSpeed, double acceleration);

    void accelerate(Direction direction);
    void deaccelerate(Direction direction);

    void frameUpdate(bool &colided);

    Vector2d getSpeed() const;
    Vector2d getPosition() const;

    string printDirections() const;
    void printBody() const;
};
} // namespace physics