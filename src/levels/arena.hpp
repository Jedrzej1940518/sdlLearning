#pragma once

#include "utils.hpp"
#include "level.hpp"

#include "rendering/object.hpp"
#include "rendering/collisionObject.hpp"
#include "physics/collisionModel.hpp"

#include "ships/playerShip.hpp"
#include "ships/projectile.hpp"

#include <vector>

#include <SFML/Graphics/Drawable.hpp>

// #include "ships/hostileShip.hpp"

namespace levels
{

  class Arena : public Level
  {
    std::vector<std::shared_ptr<sf::Drawable>> drawables;
    std::vector<std::shared_ptr<FrameUpdateable>> frameUpdateables;

    std::vector<std::shared_ptr<rendering::CollisionObject>> collidables;

    std::vector<std::shared_ptr<ships::Ship>> shooters;

    std::shared_ptr<ships::PlayerShip> controledObject;

    physics::CollisionModel collisionModel{};

  public:
    Arena(sf::RenderWindow &window, LevelType &level);
    virtual ~Arena();
    virtual void handleEvents(const sf::Event &event) override;

  private:
    // void populateArenaWithAsteroids(int x, int y);

    void cleanupDeadObjects();
    void frameUpdate();
    void draw();
    virtual void render() override;

    // debug
    void debugPrint();
  };
} // namespace levels