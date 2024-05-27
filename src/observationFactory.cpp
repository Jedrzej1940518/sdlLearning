
#include "observationFactory.hpp"
#include "prefabs/prefabs.hpp"

inline static constexpr float maxVelocity = prefabs::wolfMaxVelocity * 1.41f; // velocity component
inline static constexpr float maxHp = prefabs::hammerheadHp;

float normalizePos(float x)
{
    return std::clamp(x / std::max(config::ARENA_MAX_X, config::ARENA_MAX_Y), -1.f, 1.f);
}

float normalizeVelocity(float x)
{
    return std::clamp(x / maxVelocity, -1.f, 1.f);
}

float normalizeHp(float hp)
{
    return std::clamp(hp / maxHp, 0.f, 1.f);
}

float normalizeRotation(float radians)
{
    return std::clamp(radians / 3.14f, -1.f, 1.f);
}

sf::Vector2f normalizeRelativePos(sf::Vector2f dPos)
{
    dPos /= 800.f;
    return physics::clampVector(dPos, 1.f);
}

void fillBaseShipObs(ObservationFactory::ObservationType &obs, const ships::Ship &ship)
{
    obs.push_back(normalizeVelocity(ship.getVelocity().x));
    obs.push_back(normalizeVelocity(ship.getVelocity().y));
    obs.push_back(normalizePos(ship.getCenter().x));
    obs.push_back(normalizePos(ship.getCenter().y));
    obs.push_back(normalizeHp((float)ship.getHp()));
    obs.push_back(normalizeRotation(physics::degreesToRadians(ship.getRotationCartesian())));
}

void fillRelativeShipObs(ObservationFactory::ObservationType &obs, const ships::Ship &observer, const ships::Ship &ship)
{

    fillBaseShipObs(obs, ship);
    float angle = physics::getRelativeAngle(observer.getCenter(), ship.getCenter(), observer.getRotationCartesian());
    auto dPos = normalizeRelativePos(ship.getCenter() - observer.getCenter());

    obs.push_back(normalizeRotation(physics::degreesToRadians(angle)));
    obs.push_back(dPos.x);
    obs.push_back(dPos.y);
}

void fillDeadShip(ObservationFactory::ObservationType &obs)
{
    const int relativeObsSize = 9;

    for (int i = 0; i < relativeObsSize; ++i)
        obs.push_back(0);
}

void ObservationFactory::embbedShip(int team, int mass, ObservationFactory::ObservationType &obs, const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships)
{
    auto findShip = [&](std::shared_ptr<ships::AiShip> ship)
    {
        bool rightShip = (ship->getTeam() == team) && (ship->getMass() == mass);

        auto shipById = std::find_if(shipsObserved.begin(), shipsObserved.end(), [&](int id)
                                     { return id == ship->getShipId(); });

        bool wasObserved = shipById != shipsObserved.end();

        return rightShip && (not wasObserved);
    };

    auto ship = std::find_if(ships.begin(), ships.end(), findShip);

    if (ship != ships.end())
    {
        fillRelativeShipObs(obs, observer, **ship);
        shipsObserved.push_back((*ship)->getShipId());
    }
    else
        fillDeadShip(obs);
}

// scenario 0 is 1v1, lasher vs hammerhead
void ObservationFactory::fillScenario0(ObservationFactory::ObservationType &obs, const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships)
{
    obs.reserve(32);
    fillBaseShipObs(obs, observer);
    int enemyTeam = observer.getTeam() == config::BLUE_TEAM ? config::RED_TEAM : config::BLUE_TEAM;
    embbedShip(enemyTeam, prefabs::hammerheadMass, obs, observer, ships);
}
// scenario 1 is 1v3, lasher vs hammerhead and 2 scarabs
void ObservationFactory::fillScenario1(ObservationFactory::ObservationType &obs, const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships)
{
    obs.reserve(48);
    fillBaseShipObs(obs, observer);
    int enemyTeam = observer.getTeam() == config::BLUE_TEAM ? config::RED_TEAM : config::BLUE_TEAM;
    embbedShip(enemyTeam, prefabs::hammerheadMass, obs, observer, ships);
    embbedShip(enemyTeam, prefabs::scarabMass, obs, observer, ships);
    embbedShip(enemyTeam, prefabs::scarabMass, obs, observer, ships);
}
// scenario 2 is 2v3 lasher+hammerhead vs hammerhead and 2 scarabs
void ObservationFactory::fillScenario2(ObservationFactory::ObservationType &obs, const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships)
{
    obs.reserve(64);
    fillBaseShipObs(obs, observer);
    embbedShip(observer.getTeam(), prefabs::hammerheadMass, obs, observer, ships);

    int enemyTeam = observer.getTeam() == config::BLUE_TEAM ? config::RED_TEAM : config::BLUE_TEAM;
    embbedShip(enemyTeam, prefabs::hammerheadMass, obs, observer, ships);
    embbedShip(enemyTeam, prefabs::scarabMass, obs, observer, ships);
    embbedShip(enemyTeam, prefabs::scarabMass, obs, observer, ships);
}

ObservationFactory::ObservationType ObservationFactory::makeObservation(const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships)
{
    auto start = std::chrono::high_resolution_clock::now();

    ObservationType obs{};

    switch (scenario)
    {
    case 0:
        fillScenario0(obs, observer, ships);
        break;

    case 1:
        fillScenario1(obs, observer, ships);
        break;
    case 2:
        fillScenario2(obs, observer, ships);
        break;

    default:
        break;
    }

    shipsObserved.clear();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    globals::TIMER->addTime(globals::MakeObsFunction, duration.count());

    return obs;
}
