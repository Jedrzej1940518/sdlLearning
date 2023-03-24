#pragma once

#include "../physics/body.hpp"
#include "../physics/collisionModel.hpp"
#include "../rendering/chatbox.hpp"
#include "../rendering/collisionObject.hpp"
#include "../sdl.hpp"
#include "../utils.hpp"
#include "level.hpp"
#include <vector>

namespace levels
{

class Arena : public Level
{
    using CollisionObject = rendering::CollisionObject;

    SDL_Texture *texture;
    SDL_Rect viewport;
    rendering::Chatbox chatbox;
    rendering::Object background{"../data/graphics/backgrounds/background3.jpg", {3000, 3000}, "background", 0.8};

    CollisionObject *controledObject;

    vector<CollisionObject> collidableObjects;
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