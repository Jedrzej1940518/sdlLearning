#pragma once

#include "physics.hpp"
#include <array>

namespace physics
{

  class Body
  {
    uint mass;

    Vector2d speed;
    double maxSpeed;
    double acceleration;

    double rotation;

    bool accelerating;

  public:
    Body(uint mass, Vector2d speed, double maxSpeed, double acceleration, double rotation);

    void accelerate();
    void deaccelerate();

    void rotate(double degrees);

    void handleColision(CollisionParams &collisionParams);

    void frameUpdate(CollisionParams &collisionParams);

    Vector2d &getSpeed();
    double getRotation();
    uint getMass();

    void printBody() const;
  };
} // namespace physics