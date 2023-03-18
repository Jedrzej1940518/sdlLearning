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
    GridPosition gridPosition;

  public:
    CollisionObject(string &&texturePath, string &&id, Vector2d &&position, Body &&body);
    void collisionCheck(CollisionObject &oth);

    void frameUpdate(physics::CollisionModel &collisionModel);

    void printGridPosition() const;
    void printSpeed();

    int getWidth() const;
    int getHeight() const;
    GridPosition &getGridPosition();
    Body &getBody();
};
} // namespace rendering