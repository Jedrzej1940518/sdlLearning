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
    sf::Vector2f acceleration;
    float rotation;

    float rotationLeft;
    bool acceleratingOnce;

    float maxRotationSpeed;
    float maxVelocity;
    float maxAcceleration;
    float mass;

  public:
    Body(float maxRotationSpeed, float maxVelocity, float maxAcceleration, float mass);

    void frameUpdate() override;

    void accelerateOnce(sf::Vector2f accelerationVector);
    void rotateOnce(float degrees);
    void applyCollision(const CollisionParams &cp);

    // setters
    void setPosition(const sf::Vector2f& p) { position = p; }
    void setVelocity(const sf::Vector2f& v) { velocity = physics::clampVector(v, maxVelocity); }
    void setRotation(float r) { rotation = physics::normalizeDegrees(r); }

    // getters
    const sf::Vector2f &getVelocity() const { return velocity; }
    const sf::Vector2f &getPosition() const { return position; }
    float getMaxVelocity() const { return maxVelocity; }
    float getMaxAcceleration() const { return maxAcceleration; }
    float getRotation() const { return rotation; }
    float getRotationLeft() { return rotationLeft; }
    float getMass() const { return mass; }
  };
} // namespace physics