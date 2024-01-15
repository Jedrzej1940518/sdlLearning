#pragma once

#include "physics/body.hpp"
#include "physics/physics.hpp"
#include "physics/collisionModel.hpp"
// #include "rendering/arena_ui/console.hpp"
#include "rendering/collisionObject.hpp"
#include "mySdl.hpp"
#include "utils.hpp"
#include "level.hpp"
#include <vector>

#include "ships/ship.hpp"
#include "ships/hostileShip.hpp"

namespace levels
{

  class Arena : public Level
  {
    using CollisionObject = rendering::CollisionObject;

   // SDL_Texture *texture;
    SDL_Rect viewport;
    //  rendering::console console;
    rendering::Object background{getDataPath("data/graphics/backgrounds/background3.jpg").c_str(), {3000, 3000}, "background", 1};

    ships::Ship *controledObject;

    vector<CollisionObject *> collidableObjects;
    vector<ships::Projectile *> projectiles;
    vector<ships::HostileShip *> hostileShips;

    static constexpr physics::GridParams gridParams{10000, 10000, 500};
    physics::CollisionModel collisionModel{gridParams};

  public:
    Arena();
    virtual ~Arena();
    virtual void handleEvent(SDL_Event &event, LevelType &levelType, bool & /**/, bool & /**/) override;

  private:
    void moveViewport();
    void populateArenaWithAsteroids(int x, int y);
    virtual void render() override;
  };
} // namespace levels