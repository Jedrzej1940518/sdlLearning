#pragma once

#include "../physics/body.hpp"
#include "../rendering/collisionObject.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include "level.hpp"
#include <vector>

namespace levels
{
class Arena : public Level
{
    SDL_Texture *texture;
    SDL_Rect viewport;
    rendering::Object background{"../data/graphics/backgrounds/background3.jpg", {0, 0}, 0.2};
    rendering::CollisionObject ship{"../data/graphics/ships/scarab.png",
                                    physics::Body{{500, 500}, {0, 0}, {10, 10}, 0.5}};
    rendering::CollisionObject *controledObject{&ship};

  public:
    Arena();
    virtual void handleEvent(const SDL_Event &event, LevelType &levelType, bool & /**/) override;

  private:
    void moveViewport();
    virtual void render() override;
};
} // namespace levels