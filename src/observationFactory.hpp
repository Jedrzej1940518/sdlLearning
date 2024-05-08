
#pragma once

#include "ships/aiShip.hpp"

class ObservationFactory
{
public:
    static constexpr int maxShips = config::BLUE_TEAM_SHIPS + config::RED_TEAM_SHIPS;

    static constexpr int baseObsSize = 4;
    static constexpr int relativeObsSize = 8;

    static constexpr int totalObsSize = baseObsSize + (maxShips - 1) * relativeObsSize;

    using BaseObsType = std::array<float, baseObsSize>;
    using RelativeObsType = std::array<float, relativeObsSize>;
    using ObservationType = std::array<float, totalObsSize>;

public:
    ObservationType makeObservation(const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships);
};