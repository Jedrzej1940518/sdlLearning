#include "collisionModel.hpp"
namespace physics
{

    CollisionModel::CollisionModel(GridParams gridParams)
        : gridParams{gridParams}, rows{gridParams.mapHeight / gridParams.cellSide + 1}, columns{gridParams.mapWidth /
                                                                                                    gridParams.cellSide +
                                                                                                1}
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

    void CollisionModel::debugPrint(const std::string &s)
    {
        std::cout << "----" << s << "-----" << std::endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                for (auto *object : grid[i][j])
                {
                    printf("[%i][%i][%zi] ", i, j, grid[i][j].size());
                    object->printGridPosition();
                }
        std::cout << std::endl;
    }
    void CollisionModel::collides(CollisionObject &obj, GridCoords &neigh)
    {
        for (auto *neighObject : grid[neigh.row][neigh.column])
            obj.collisionCheck(*neighObject);
    }

    void CollisionModel::checkCollisions()
    {
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
    void CollisionModel::remove(const CollisionObject &obj)
    {
        auto &g = obj.getGridPosition();
        auto &vec = grid[g.row][g.column];

        removeVectorElement(vec, g.index);
    }

    void CollisionModel::emplace(CollisionObject &obj)
    {
        auto g = calculateGridCoords(obj.getCenter());
        int column = g.column;
        int row = g.row;

        grid[row][column].push_back(&obj);
        int indx = static_cast<int>(grid[row][column].size()) - 1;
        obj.setGridPosition({row, column, indx});
    }

    void CollisionModel::recalculateGridPositions()
    {
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < columns; ++c)
                for (int i = 0; i < grid[r][c].size(); ++i)
                {
                    auto *obj = grid[r][c][i];
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
                }
    }

    const GridParams &CollisionModel::getGridParams()
    {
        return gridParams;
    }

} // namespace physics