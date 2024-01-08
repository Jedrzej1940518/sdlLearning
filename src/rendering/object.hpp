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
    physics::Vector2d position;
    string id;
    double parallaxFactor;

  public:
    Object(const string &texturePath, physics::Vector2d &position, const string &id, double parallaxFactor = 1.0);
    Object(string &&texturePath, physics::Vector2d &&position, string &&id, double parallaxFactor = 1.0);

    void printPosition() const;

    void frameUpdate(physics::Vector2d offset);
    virtual void renderObject(SDL_Rect viewport);

    int getX();
    int getY();
    physics::Vector2d &getPosition();
    SDL_Rect getDstrect();
    const string &getId() { return id; }

    ~Object()
    {
    }
  };
} // namespace rendering
