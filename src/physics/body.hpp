#pragma once

#include "physics.hpp"
#include <array>
#include "hardware.hpp"

namespace physics
{
  class Body
  {
  protected:
    Vector2d bounce;
    Vector2d velocity;
    double rotation;
    Hardware hardware;

    double rotationLeft;

    bool accelerating;

    double accelerationAngle;
    bool acceleratingOnce;

  public:
    Body(Hardware hardware);
    Body(Vector2d velocity, double rotation, Hardware hardware);

    void accelerate();
    void accelerateOnce(double angle);
    void deaccelerate();

    void rotate(double degrees);
    void rotateOnce(DIRECTION rd);

    void handleColision(CollisionParams &collisionParams);

    void frameUpdate(CollisionParams &collisionParams);

    Vector2d &getSpeed();
    const Vector2d &getSpeed() const;
    Vector2d applyBounce();
    double getRotation() const;
    double getRotationLeft();
    double getAccelerationAngle() const;
    uint getMass();

    void printBody() const;
  };
} // namespace physics