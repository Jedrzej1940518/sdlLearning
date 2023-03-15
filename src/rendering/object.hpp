#pragma once

#include "../physics/body.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include <SDL2/SDL_rect.h>

namespace rendering
{
class Object
{
    using Body = physics::Body;

  protected:
    SDL_Texture *texture;
    SDL_Rect dstrect;
    double parallaxFactor;

  public:
    Object(string texturePath, SDL_Rect dstrect, double parallaxFactor = 1);

    void printPosition() const;

    void frameUpdate(Vector2d offset);
    void renderObject(SDL_Rect viewport);

    int getX();
    int getY();
    SDL_Rect getDstrect();
};
} // namespace rendering
