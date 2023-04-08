#pragma once

#include "../physics/body.hpp"
#include "../physics/physics.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include "object.hpp"
#include <SDL2/SDL_rect.h>

namespace physics
{
  class CollisionModel;
};

namespace rendering
{
  class CollisionObject : public Object
  {
    using Body = physics::Body;
    using CollisionModel = physics::CollisionModel;

    Body body;
    physics::CollisionParams collisionParams;
    physics::GridPosition gridPosition;

  public:
    CollisionObject(string &&texturePath, string &&id, physics::Vector2d &&position, Body &&body);
    void collisionCheck(CollisionObject &oth);

    void frameUpdate(physics::CollisionModel &collisionModel);
    void renderObject(SDL_Rect viewport) override;
    void printCollisionObject() const;
    void printGridPosition() const;
    void printSpeed() const;

    int getWidth() const;
    int getHeight() const;
    physics::GridPosition &getGridPosition();
    Body &getBody();
  };
} // namespace rendering