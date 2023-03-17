#pragma once

#include "../physics/body.hpp"
#include "../physics/physics.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include "object.hpp"
#include <SDL2/SDL_rect.h>

namespace rendering
{
class CollisionObject : public Object
{
    using Body = physics::Body;

    Body body;
    physics::CollisionParams collisionParams;
    GridPosition gridPosition;

  public:
    CollisionObject(string &&texturePath, string &&id, Vector2d &&position, Body &&body);
    static void collisionCheck(CollisionObject &a, CollisionObject &b);

    void frameUpdate();

    void printGridPosition() const;
    void printSpeed() const;

    int getWidth() const;
    int getHeight() const;
    GridPosition &getGridPosition();
    Body &getBody();
};
} // namespace rendering