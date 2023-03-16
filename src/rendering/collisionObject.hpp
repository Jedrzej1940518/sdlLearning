#pragma once

#include "../physics/body.hpp"
#include "../physics/physics.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include "object.hpp"
#include <SDL2/SDL_rect.h>

namespace rendering
{
struct Collison
{
    bool collided;
    Vector2d speedSum;
};
class CollisionObject : public Object
{
    using Body = physics::Body;

    Body body;
    Collison collison;

  public:
    CollisionObject(string texturePath, Body body);

    bool collides(const CollisionObject &other);
    void frameUpdate();

    int getWidth() const;
    int getHeight() const;
    Body &getBody();
};
} // namespace rendering