#pragma once

// #include "physics/body.hpp"
// #include "physics/physics.hpp"
#include "physics/collisionModel.hpp"

#include "utils.hpp"
#include "level.hpp"

#include "rendering/Object.hpp"
#include "rendering/collisionObject.hpp"

#include <vector>

#include "ships/ship.hpp"
// #include "ships/hostileShip.hpp"

namespace levels
{

  class Arena : public Level
  {
    // using CollisionObject = rendering::CollisionObject;

    // SDL_Texture *texture;
    // SDL_Rect viewport;
    //  rendering::console console;

    std::vector<std::shared_ptr<rendering::Object>> objects;
    std::vector<std::shared_ptr<rendering::CollisionObject>> collidables;
    std::shared_ptr<ships::Ship> controledObject;
    // vector<CollisionObject *> collidableObjects;
    // vector<ships::Projectile *> projectiles;
    // vector<ships::HostileShip *> hostileShips;

    static constexpr physics::GridParams gridParams{10000, 10000, 500};
    physics::CollisionModel collisionModel{gridParams};

  public:
    Arena(sf::RenderWindow &window, LevelType &level);
    virtual ~Arena();
    virtual void handleEvents(const sf::Event &event) override;

  private:
    // void moveViewport();
    // void populateArenaWithAsteroids(int x, int y);
    void frameUpdate();
    void draw();
    virtual void render() override;
  };
} // namespace levels