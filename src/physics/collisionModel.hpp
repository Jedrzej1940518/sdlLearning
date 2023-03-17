#pragma once

#include "../rendering/collisionObject.hpp"
#include <cstdint>
#include <sys/types.h>
#include <vector>

namespace physics
{
struct GridCoords
{
    int row;
    int column;
};

template <uint mapWidth, uint mapHeight, uint gridSide> class CollisionModel
{
    using CollisionObject = rendering::CollisionObject;

    int rows;
    int columns;

    //[rows][columns] of vector<CollisonObject*>
    using Grid = vector<CollisionObject *>[mapHeight / gridSide + 1][mapWidth / gridSide + 1];

    Grid grid;

  public:
    CollisionModel() : rows{mapHeight / gridSide + 1}, columns{mapWidth / gridSide + 1}
    {
    }

  private:
    void collides(GridCoords &&a, GridCoords &&neigh)
    {
        if (neigh.column < 0 || neigh.row < 0 || neigh.column >= columns || neigh.row >= rows)
            return;

        for (auto *object : grid[a.row][a.column])
            for (auto *neighObject : grid[neigh.row][neigh.column])
                rendering::CollisionObject::collisionCheck(*object, *neighObject);
    }

  public:
    void checkCollisions()
    {

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                for (int n = j - 1; n <= j + 1; ++n)     // check neigbours
                    for (int m = i - 1; m <= i + 1; ++m) // so n, m should be 9 grids
                        collides(GridCoords{i, j}, GridCoords{n, m});
    }
    void remove(CollisionObject &obj)
    {
        auto &g = obj.getGridPosition();
        auto lastIndex = static_cast<int>(grid[g.row][g.column].size()) - 1;

        std::swap(grid[g.row][g.column][lastIndex], grid[g.row][g.column][g.index]);

        grid[g.row][g.column][lastIndex]->getGridPosition().index = g.index;
        grid[g.row][g.column].pop_back();
    }

    GridPosition emplace(CollisionObject *obj)
    {
        int column = obj->getX() / gridSide;
        int row = obj->getY() / gridSide;

        grid[row][column].push_back(obj);
        int indx = static_cast<int>(grid[row][column].size()) - 1;
        obj->getGridPosition() = {row, column, indx};

        return {row, column, indx};
    }

    void recalculateGridPosition(CollisionObject &obj)
    {
        int column = obj.getX() / gridSide;
        int row = obj.getY() / gridSide;
        auto &g = obj.getGridPosition();

        if (g.column != column || g.row != row)
        {
            remove(obj);
            g = emplace(&obj);
        }
    }
};
} // namespace physics