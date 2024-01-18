#pragma once

#include "physics.hpp"
#include "frameUpdateable.hpp"

#include <array>

#include <SFML/System/Vector2.hpp>

namespace physics
{
  class Body : public FrameUpdateable
  {
    sf::Vector2f position;
    sf::Vector2f velocity;
    float rotation;

    float rotationLeft;
    float accelerationAngle;
    bool acceleratingOnce;

    float maxRotationSpeed;
    float maxVelocity;
    float maxAcceleration;
    float mass;

  public:
    Body(float maxRotationSpeed, float maxVelocity, float maxAcceleration, float mass);

    void frameUpdate() override;

    void accelerateOnce(float angle);
    void rotateOnce(float degrees);
    void applyCollision(const CollisionParams &cp);

    // setters
    void setPosition(sf::Vector2f p) { position = p; }
    void setVelocity(sf::Vector2f v) { velocity = v; }
    void setRotation(float r) { rotation = r; }

    // getters
    const sf::Vector2f &getVelocity() const { return velocity; }
    const sf::Vector2f &getPosition() const { return position; }
    float getRotation() const { return rotation; }
    float getRotationLeft() { return rotationLeft; }
    float getAccelerationAngle() const { return accelerationAngle; }
    float getMass() const { return mass; }
  };
} // namespace physics