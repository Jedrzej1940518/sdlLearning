#pragma once

#include "../physics/body.hpp"
#include "../physics/physics.hpp"
#include "../physics/collisionModel.hpp"
// #include "../rendering/arena_ui/console.hpp"
#include "../rendering/collisionObject.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include "level.hpp"
#include <vector>

#include "../ships/ship.hpp"

namespace levels
{

  class Arena : public Level
  {
    using CollisionObject = rendering::CollisionObject;

    SDL_Texture *texture;
    SDL_Rect viewport;
    //  rendering::console console;
    rendering::Object background{"../data/graphics/backgrounds/background3.jpg", {3000, 3000}, "background", 0.4};

    ships::Ship *controledObject;

    vector<CollisionObject *> collidableObjects;
    static constexpr physics::GridParams gridParams{10000, 10000, 500};
    physics::CollisionModel collisionModel{gridParams};

  public:
    Arena();
    virtual void handleEvent(SDL_Event &event, LevelType &levelType, bool & /**/) override;

  private:
    void moveViewport();
    virtual void render() override;
  };
} // namespace levels