#pragma once

#include "../physics/body.hpp"
#include "../rendering/controllableObject.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include "level.hpp"

namespace levels
{
class Arena : public Level
{
    SDL_Texture *texture;
    SDL_Rect viewport;
    rendering::ControllableObject ship{
        "../data/graphics/ships/scarab.png", {500, 500, 100, 100}, physics::Body{{0, 0}, {10, 10}, 1}};
    rendering::ControllableObject *controledObject{&ship};

  public:
    Arena();
    virtual void handleEvent(const SDL_Event &event, LevelType &levelType, bool & /**/) override;

  private:
    void moveViewport();
    virtual void render() override;
};
} // namespace levels