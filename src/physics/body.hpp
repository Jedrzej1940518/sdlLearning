#pragma once

#include "physics.hpp"
#include <array>
#include "hardware.hpp"

namespace physics
{

  class Body
  {

    Vector2d speed;
    double rotation;
    Hardware hardware;

    double rotationLeft;
    bool accelerating;

  public:
    Body(Hardware hardware);
    Body(Vector2d speed, double rotation, Hardware hardware);

    void accelerate();
    void deaccelerate();

    void rotate(double degrees);

    void handleColision(CollisionParams &collisionParams);

    void frameUpdate(CollisionParams &collisionParams);

    Vector2d &getSpeed();
    const Vector2d &getSpeed() const;
    double getRotation();
    uint getMass();

    void printBody() const;
  };
} // namespace physics