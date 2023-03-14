#pragma once

#include "../object.hpp"
#include "../physics/body.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include "level.hpp"

namespace levels
{
class Arena : public Level
{
    SDL_Texture *texture;
    SDL_Rect viewport;
    Object ship{"../data/graphics/ships/scarab.png", physics::Body{{500, 500}, {0, 0}, {5, 5}, 1, Direction::NONE}};

    Object *controledObject{&ship};

  public:
    Arena();
    virtual void handleEvent(const SDL_Event &event, LevelType &levelType, bool & /**/) override;

  private:
    void moveViewport();
    virtual void render() override;
};
} // namespace levels