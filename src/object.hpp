#pragma once

#include "physics/body.hpp"
#include "sdl.hpp"
#include "utils.hpp"
#include <SDL2/SDL_rect.h>

class Object
{
    using Body = physics::Body;

    SDL_Texture *texture;
    SDL_Rect dstrect;
    Body body;

  public:
    Object(string texturePath, SDL_Point position);
    Object(string texturePath, Body body);

    void frameUpdate(SDL_Rect viewport);

    void printObject() const
    {
        printf("Position {%u, %u}\n", body.getPosition().x, body.getPosition().y);
    }
    int getWidth() const
    {
        return dstrect.w;
    }
    int getHeight() const
    {
        return dstrect.h;
    }
    Body &getBody()
    {
        return body;
    }

  private:
    void renderObject(SDL_Rect viewport);
};
