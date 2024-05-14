
#pragma once

#include "ships/aiShip.hpp"

class ObservationFactory
{
public:
    using ObservationType = std::vector<float>;

private:
    int scenario;
    std::vector<int> shipsObserved{};
    void embbedShip(int team, int mass, ObservationFactory::ObservationType &obs, const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships);

    void fillScenario0(ObservationFactory::ObservationType &obs, const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships);
    void fillScenario1(ObservationFactory::ObservationType &obs, const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships);
    void fillScenario2(ObservationFactory::ObservationType &obs, const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships);

public:
    ObservationFactory(int scenario) : scenario{scenario} {}
    ObservationType makeObservation(const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships);
};