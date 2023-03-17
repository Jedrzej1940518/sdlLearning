#pragma once

#include "../physics/body.hpp"
#include "../physics/collisionModel.hpp"
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
    rendering::Object background{"../data/graphics/backgrounds/background3.jpg", {0, 0}, "background", 0.2};

    CollisionObject *controledObject;

    vector<CollisionObject> collidableObjects;
    physics::CollisionModel<10000, 10000, 500> collisionModel;

  public:
    Arena();
    virtual void handleEvent(const SDL_Event &event, LevelType &levelType, bool & /**/) override;

  private:
    void moveViewport();
    virtual void render() override;
};
} // namespace levels