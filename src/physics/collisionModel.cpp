#include "collisionModel.hpp"

namespace physics
{
    template <typename Collidable, typename Grid>
    void t_emplace(GridCoords g, Collidable &obj, Grid &grid)
    {
        int row = g.row;
        int column = g.column;

        grid[row][column].push_back(&obj);
        int indx = static_cast<int>(grid[row][column].size()) - 1;
        obj.setGridPosition({row, column, indx});
    }

    template <typename Grid>
    void t_remove(GridPosition g, Grid &grid)
    {
        auto &vec = grid[g.row][g.column];
        removeVectorElement(vec, g.index);
    }

    CollisionModel::CollisionModel(GridParams gridParams)
        : gridParams{gridParams}, rows{gridParams.mapHeight / gridParams.cellSide + 1}, columns{gridParams.mapWidth /
                                                                                                    gridParams.cellSide +
                                                                                                1}
    {
        for (int i = 0; i < rows; ++i)
        {
            grid.push_back({});
            pGrid.push_back({});
            for (int j = 0; j < columns; ++j)
            {
                grid[i].push_back({});
                pGrid[i].push_back({});
            }
        }
    }

    void CollisionModel::debugPrint(const std::string &s)
    {
        std::cout << "----" << s << "-----" << std::endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                for (auto *object : grid[i][j])
                {
                    auto gp = object->getGridPosition();
                    printf("[%i][%i] objects [%zi] | %s [%i][%i][%i]\n", i, j, grid[i][j].size(), object->getId().c_str(), gp.row, gp.column, gp.index);
                }
        std::cout << std::endl;
    }
    void CollisionModel::collides(CollisionObject &obj, GridCoords &neigh)
    {
        for (auto *neighObject : grid[neigh.row][neigh.column])
            if (neighObject != &obj && obj.collisionHappening(neighObject->getCollisionCircle()))
                obj.handleCollision(*neighObject);

        for (auto *neightProjectile : pGrid[neigh.row][neigh.column])
            if (obj.collisionHappening(neightProjectile->getCollisionCircle()))
                neightProjectile->handleCollision(obj);
    }

    void CollisionModel::inputCollisions()
    {
        // debugPrint("debugging");
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < columns; ++c)
                for (auto &obj : grid[r][c])
                {
                    const auto &gridPos = obj->getGridPosition();
                    int i = gridPos.row;
                    int j = gridPos.column;

                    for (int n = i - 1; n <= i + 1; ++n)     // check neigbours
                        for (int m = j - 1; m <= j + 1; ++m) // so n, m should be 9 grids
                        {
                            GridCoords neigh{n, m};
                            if (neigh.column < 0 || neigh.row < 0 || neigh.column >= columns || neigh.row >= rows)
                                continue;

                            collides(*obj, neigh);
                        }
                }
    }
    GridCoords CollisionModel::calculateGridCoords(const sf::Vector2f &v)
    {
        int row = std::clamp(static_cast<int>(v.x) / gridParams.cellSide, 0, rows - 1);
        int column = std::clamp(static_cast<int>(v.y) / gridParams.cellSide, 0, columns - 1);
        return {row, column};
    }

    // recalculates objects in grid and deletes dead objects
    void CollisionModel::frameUpdate()
    {
        auto moveObjectsInGrid = [&]<typename Vec>(Vec &vec)
        {
        for (int i = 0; i < vec.size(); ++i)
        {
            auto *obj = vec[i];
            if(not obj->isAlive()) {
                remove(*obj);
                continue;
            }

            auto gp = calculateGridCoords(obj->getCenter());
            int column = gp.column;
            int row = gp.row;

            auto &g = obj->getGridPosition();

            if (g.column != column || g.row != row)
            {
                remove(*obj);
                emplace(*obj);
                continue;
            }
        } };

        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < columns; ++c)
            {
                moveObjectsInGrid(grid[r][c]);
                moveObjectsInGrid(pGrid[r][c]);
            }
    }

    const GridParams &CollisionModel::getGridParams()
    {
        return gridParams;
    }

    void CollisionModel::remove(const CollisionObject &obj) { t_remove(obj.getGridPosition(), grid); };
    void CollisionModel::emplace(CollisionObject &obj) { t_emplace(calculateGridCoords(obj.getCenter()), obj, grid); };

    void CollisionModel::remove(const Projectile &proj) { t_remove(proj.getGridPosition(), pGrid); };
    void CollisionModel::emplace(Projectile &proj) { t_emplace(calculateGridCoords(proj.getCenter()), proj, pGrid); };

} // namespace physics