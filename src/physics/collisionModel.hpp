#pragma once

#include "rendering/collisionObject.hpp"
#include "ships/projectile.hpp"

#include "physics.hpp"
#include <cstdint>
#include <sys/types.h>
#include <vector>

namespace physics
{
  class CollisionModel
  {
    using CollisionObject = rendering::CollisionObject;
    using Projectile = ships::Projectile;

    //[rows][columns] of std::list<CollisonObject*>
    using CollisionObjectGrid = std::vector<std::vector<std::vector<CollisionObject *>>>; // todo use smart ptr here probably
                                                                                          // also switch to anything else please
    using ProjectilesGrid = std::vector<std::vector<std::vector<Projectile *>>>;

    GridParams gridParams;
    int rows;
    int columns;

    CollisionObjectGrid grid;
    ProjectilesGrid pGrid;

  public:
    CollisionModel(GridParams gridParams);

  private:
    void debugPrint(const std::string &s);
    void collides(CollisionObject &obj, GridCoords &neigh);

  public:
    void inputCollisions();
    void frameUpdate();

    GridCoords calculateGridCoords(const sf::Vector2f &v);

    void emplace(CollisionObject &obj);
    void emplace(Projectile &proj);
    void remove(const CollisionObject &obj);
    void remove(const Projectile &proj);

    const GridParams &getGridParams();
  };
} // namespace physics