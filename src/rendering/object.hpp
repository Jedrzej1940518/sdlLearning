#pragma once

#include "physics/body.hpp"
#include "mySdl.hpp"
#include "utils.hpp"
#include "soundManager.hpp"
#include <unordered_set>
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
    std::unordered_set<Sound> soundsToPlay;

  public:
    Object(const string &texturePath, physics::Vector2d &position, const string &id, double parallaxFactor = 1.0);
    Object(string &&texturePath, physics::Vector2d &&position, string &&id, double parallaxFactor = 1.0);

    void printPosition() const;

    void frameUpdate(physics::Vector2d offset);
    void playSounds();
    virtual void renderObject(SDL_Rect viewport);

    int getX();
    int getY();
    physics::Vector2d getPosition() const;
    SDL_Rect getDstrect();
    const string &getId() { return id; }

    virtual ~Object()
    {
      SDL_DestroyTexture(texture);
    }
  };
} // namespace rendering
