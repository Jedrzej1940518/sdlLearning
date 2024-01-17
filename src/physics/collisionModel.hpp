#pragma once

#include "rendering/collisionObject.hpp"
#include "physics.hpp"
#include <cstdint>
#include <sys/types.h>
#include <vector>

namespace physics
{
  class CollisionModel
  {
    using CollisionObject = rendering::CollisionObject;

    //[rows][columns] of vector<CollisonObject*>
    using Grid = std::vector<std::vector<std::vector<CollisionObject *>>>; // todo use smart ptr here probably

    GridParams gridParams;
    int rows;
    int columns;
    Grid grid;

  public:
    CollisionModel(GridParams gridParams);

  private:
    void debugPrint(const std::string &s);
    void collides(CollisionObject &obj, GridCoords &neigh);

  public:
    void frameUpdate();

    void checkCollisions();
    void recalculateGridPositions();

    GridCoords calculateGridCoords(const sf::Vector2f &v);

    void remove(const CollisionObject &obj);
    void emplace(CollisionObject &obj);

    const GridParams &getGridParams();
  };
} // namespace physics