

#include "../rendering/collisionObject.hpp"
#include <cstdint>
#include <sys/types.h>
#include <vector>

namespace physics
{
struct GridCoords
{
    uint32_t row;
    uint32_t column;
};
template <uint32_t rows, uint32_t columns> class collisionModel
{
    using CollisionObject = rendering::CollisionObject;
    using Grid = std::vector<rendering::CollisionObject *>[rows][columns];

    Grid grid;
    void emplace(GridCoords gridCoords, CollisionObject *object)
    {
        if (!object)
            return;

        grid[gridCoords.row][gridCoords.column].push_back(object);
    }
};
} // namespace physics