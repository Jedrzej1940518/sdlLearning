
#pragma once

#include "ships/aiShip.hpp"

class ObservationFactory
{
public:
    static constexpr int maxShips = 5;

    static constexpr int baseObsSize = 16;
    static constexpr int relativeObsSize = 20;

    static constexpr int totalObsSize = baseObsSize + maxShips * relativeObsSize;

    using BaseObsType = std::array<float, baseObsSize>;
    using RelativeObsType = std::array<float, relativeObsSize>;
    using ObservationType = std::array<float, totalObsSize>;
    using Observations = std::vector<ObservationType>;

    Observations makeObservations(const std::vector<std::shared_ptr<ships::AiShip>> &ships);

private:
    ObservationType makeObservation(const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships);
};