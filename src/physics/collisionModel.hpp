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
    CollisionModel(GridParams gridParams)
        : gridParams{gridParams}, rows{gridParams.mapHeight / gridParams.cellSide + 1},
          columns{gridParams.mapWidth / gridParams.cellSide + 1}
    {
        for (int i = 0; i < rows; ++i)
        {
            grid.push_back({});
            for (int j = 0; j < columns; ++j)
            {
                grid[i].push_back({});
            }
        }
    }

  private:
    void debugPrint(string &&s)
    {
        cout << s << endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                for (auto *object : grid[i][j])
                {
                    printf("[%i][%i][%li] ", i, j, grid[i][i].size());
                    object->printGridPosition();
                }
        cout << endl;
    }
    void collides(GridCoords &&a, GridCoords &&neigh)
    {
        if (neigh.column < 0 || neigh.row < 0 || neigh.column >= columns || neigh.row >= rows)
            return;

        for (auto *object : grid[a.row][a.column])
            for (auto *neighObject : grid[neigh.row][neigh.column])
                object->collisionCheck(*neighObject);
    }

  public:
    void checkCollisions()
    {

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                for (int n = i - 1; n <= i + 1; ++n)     // check neigbours
                    for (int m = j - 1; m <= j + 1; ++m) // so n, m should be 9 grids
                        collides(GridCoords{i, j}, GridCoords{n, m});
    }
    GridCoords calculateGridCoords(int x, int y)
    {
        int row = std::clamp(x / static_cast<int>(gridParams.cellSide), 0, rows - 1);
        int column = std::clamp(y / static_cast<int>(gridParams.cellSide), 0, columns - 1);
        return {row, column};
    }
    void remove(CollisionObject &obj)
    {
        auto &g = obj.getGridPosition();
        auto lastIndex = static_cast<int>(grid[g.row][g.column].size()) - 1;
        auto &vec = grid[g.row][g.column];

        vec[lastIndex]->getGridPosition().index = g.index;
        std::swap(vec[lastIndex], vec[g.index]);

        grid[g.row][g.column].pop_back();
    }

    void emplace(CollisionObject *obj)
    {
        auto gp = calculateGridCoords(obj->getX(), obj->getY());
        int column = gp.column;
        int row = gp.row;

        grid[row][column].push_back(obj);
        int indx = static_cast<int>(grid[row][column].size()) - 1;
        obj->getGridPosition() = {row, column, indx};
    }

    void recalculateGridPosition(CollisionObject &obj)
    {
        auto gp = calculateGridCoords(obj.getX(), obj.getY());
        int column = gp.column;
        int row = gp.row;

        auto &g = obj.getGridPosition();

        if (g.column != column || g.row != row)
        {
            remove(obj);
            emplace(&obj);
        }
    }

    const GridParams &getGridParams() const
    {
        return gridParams;
    }
};
} // namespace physics