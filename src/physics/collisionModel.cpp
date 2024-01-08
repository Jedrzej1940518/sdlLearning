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

    void CollisionModel::debugPrint(const string &s)
    {
        cout << "----" << s << "-----" << endl;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                for (auto *object : grid[i][j])
                {
                    printf("[%i][%i][%li] ", i, j, grid[i][i].size());
                    object->printGridPosition();
                }
        cout << endl;
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
    GridCoords CollisionModel::calculateGridCoords(int x, int y)
    {
        int row = std::clamp(x / static_cast<int>(gridParams.cellSide), 0, rows - 1);
        int column = std::clamp(y / static_cast<int>(gridParams.cellSide), 0, columns - 1);
        return {row, column};
    }
    void CollisionModel::remove(const CollisionObject &obj)
    {
        auto &g = obj.getGridPosition();
        auto lastIndex = static_cast<int>(grid[g.row][g.column].size()) - 1;
        auto &vec = grid[g.row][g.column];

        vec[lastIndex]->getGridPosition().index = g.index;
        std::swap(vec[lastIndex], vec[g.index]);

        grid[g.row][g.column].pop_back();
    }

    void CollisionModel::emplace(CollisionObject *obj)
    {
        auto gp = calculateGridCoords(obj->getX(), obj->getY());
        int column = gp.column;
        int row = gp.row;

        grid[row][column].push_back(obj);
        int indx = static_cast<int>(grid[row][column].size()) - 1;
        obj->getGridPosition() = {row, column, indx};
    }

    void CollisionModel::recalculateGridPosition(CollisionObject &obj)
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

    const GridParams &CollisionModel::getGridParams()
    {
        return gridParams;
    }

} // namespace physics