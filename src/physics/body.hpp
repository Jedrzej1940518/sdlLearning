#pragma once

#include "physics.hpp"
#include <array>
#include <SFML/System/Vector2.hpp>

namespace physics
{
  class Body
  {
  protected:
    sf::Vector2f bounce;
    sf::Vector2f velocity;
    float rotation;

    float rotationLeft;
    float accelerationAngle;
    bool acceleratingOnce;

    float maxRotationSpeed;
    float maxVelocity;
    float acceleration;
    float mass;

  public:
    Body(float maxRotationSpeed, float maxVelocity, float acceleration, float mass);
    Body(sf::Vector2f velocity, float rotation, float maxRotationSpeed, float maxVelocity, float acceleration, float mass);

    void accelerateOnce(float angle);
    void rotateOnce(DIRECTION rd);
    sf::Vector2f consumeBounce();
    void consumeCollision(CollisionParams &collisionParams);
    void frameUpdate();

    void setVelocity(sf::Vector2f v);
    void setRotation(float r);

    const sf::Vector2f &getVelocity() const;
    double getRotation() const;
    double getRotationLeft();
    double getAccelerationAngle() const;
    float getMass() const;

    void printBody() const;
  };
} // namespace physics