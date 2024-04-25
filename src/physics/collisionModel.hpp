#pragma once

#include "physics.hpp"
#include "rendering/collisionObject.hpp"
#include "ships/projectile.hpp"

#include <vector>
#include <memory>

namespace physics
{
  // SweepAndPrune algorithm
  class CollisionModel
  {
    std::vector<std::shared_ptr<rendering::CollisionObject>> collidables;
    std::vector<std::shared_ptr<ships::Projectile>> projectiles;

  public:
    CollisionModel(){};
    void add(const std::shared_ptr<rendering::CollisionObject> &collisionObject) { collidables.push_back(collisionObject); };
    void add(const std::shared_ptr<ships::Projectile> &projectile) { projectiles.push_back(projectile); };

    void clear() {collidables.clear(); projectiles.clear();}
    // calls handleCollision on every collidable A that collides with collidable B
    // and for every projectile A that collides wit collidable B
    // also automaticly removes dead elements
    void updateCollisions();
  };
} // namespace physics