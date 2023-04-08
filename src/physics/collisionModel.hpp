#pragma once

#include "../rendering/collisionObject.hpp"
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
    using Grid = vector<vector<vector<CollisionObject *>>>;

    GridParams gridParams;
    int rows;
    int columns;
    Grid grid;

  public:
    CollisionModel(GridParams gridParams);

  private:
    void debugPrint(string &&s);
    void collides(CollisionObject &obj, GridCoords &&neigh);

  public:
    void checkCollisions(CollisionObject &obj);
    GridCoords calculateGridCoords(int x, int y);
    void remove(CollisionObject &obj);

    void emplace(CollisionObject *obj);

    void recalculateGridPosition(CollisionObject &obj);

    const GridParams &getGridParams();
  };
} // namespace physics