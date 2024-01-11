#pragma once

#include "../sdl.hpp"
#include "../utils.hpp"

namespace levels
{
  class Level
  {
  public:
    virtual void handleEvent(SDL_Event &event, LevelType &levelType, bool &quit, bool &newGame) = 0;
    virtual void render() = 0;
    virtual ~Level(){};
  };
} // namespace levels