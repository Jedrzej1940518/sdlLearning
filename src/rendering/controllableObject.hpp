#pragma once

#include "../physics/body.hpp"
#include "../physics/physics.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include "object.hpp"
#include <SDL2/SDL_rect.h>

namespace rendering
{
class ControllableObject : public Object
{
    using Body = physics::Body;

    Body body;

  public:
    ControllableObject(string texturePath, Body body);

    void frameUpdate();

    int getWidth() const;
    int getHeight() const;
    Body &getBody();
};
} // namespace rendering