
#pragma once

#include "ships/ship.hpp"

class ObservationFactory
{
    static constexpr int maxShips = 1;

    static constexpr int baseObsSize = 16;
    static constexpr int relativeObsSize = 20;

    static constexpr int totalObsSize = baseObsSize + maxShips * relativeObsSize;

public:
    using BaseObsType = std::array<float, baseObsSize>;
    using RelativeObsType = std::array<float, relativeObsSize>;
    using ObservationType = std::array<float, totalObsSize>;

    ObservationType makeObservation(const ships::Ship &observer, const std::vector<std::shared_ptr<ships::Ship>> &ships);
};