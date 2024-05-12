
#include "observationFactory.hpp"

float normalizePos(float x)
{
    return std::clamp(x / 750, -1.f, 1.f);
}

float normalizeVelocity(float x)
{
    return std::clamp(x / 6, -1.f, 1.f);
}

float normalizeHp(float hp)
{
    return std::clamp(hp / 600, 0.f, 1.f);
}

float normalizeAcceleration(float maxAcceleration)
{
    return std::clamp(maxAcceleration / 1, 0.f, 1.f);
}

float normalizeRotation(float radians)
{
    return std::clamp(radians / 3.14f, -1.f, 1.f);
}

float normalizeShipRadius(float radius)
{
    return std::clamp(radius / 100, 0.f, 1.f);
}

float normalizeCooldown(float cooldown)
{
    return std::clamp(cooldown / 50, 0.f, 1.f);
}

float normalizeProjVelocity(float projVelocity)
{
    return std::clamp(projVelocity / 20, 0.f, 1.f);
}

float normalizeProjLifetime(float projLifetime)
{
    return std::clamp(projLifetime / 20, 0.f, 1.f);
}
float normalizeProjDmg(float projDmg)
{
    return std::clamp(projDmg / 5, 0.f, 1.f);
}
float normalizeProjScatter(float projScatter)
{
    return std::clamp(projScatter / 5, 0.f, 1.f);
}

sf::Vector2f normalizeRelativePos(sf::Vector2f dPos)
{
    dPos /= 500.f;
    return physics::clampVector(dPos, 1.f);
}

ObservationFactory::BaseObsType baseShipObs(const ships::Ship &ship)
{
    /*
    pos x, pos y,
    velocity_x, velocity_y, velocity_magnitude,
    hp,
    max_velocity, max_acceleration, rotation (radians), radius,
    cooldown,
    projectile speed, projectile timespan, projetile dmg, projectile scatter
    */
    // const auto &w = ship.getWeapon();
    // return ObservationFactory::BaseObsType{
    //     normalizePos(ship.getCenter().x),
    //     normalizePos(ship.getCenter().y),
    //     normalizeVelocity(ship.getVelocity().x),
    //     normalizeVelocity(ship.getVelocity().y),
    //     normalizeVelocity(physics::getVectorMagnitude(ship.getVelocity())),
    //     normalizeHp((float)ship.getHp()),
    //     normalizeVelocity(ship.getMaxVelocity()),
    //     normalizeAcceleration(ship.getMaxAcceleration()),
    //     normalizeRotation(physics::degreesToRadians(ship.getRotationCartesian())),
    //     normalizeShipRadius(ship.getRadius()),
    //     ship.getCooldown() / ship.getMaxCooldown(),
    //     normalizeCooldown(ship.getMaxCooldown()),
    //     normalizeProjVelocity(w.getMaxVelocity()),
    //     normalizeProjLifetime((float)w.getLifetime()),
    //     normalizeProjDmg((float)w.getDmg()),
    //     normalizeProjScatter(w.getScatter())};

    return ObservationFactory::BaseObsType{normalizeVelocity(ship.getVelocity().x), normalizeVelocity(ship.getVelocity().y), normalizePos(ship.getCenter().x), normalizePos(ship.getCenter().y), normalizeHp((float)ship.getHp()), normalizeRotation(physics::degreesToRadians(ship.getRotationCartesian()))};
}

ObservationFactory::RelativeObsType relativeShipObs(const ships::Ship &observer, const ships::Ship &ship)
{
    /*
    baseShipObs,
    team (-1 enemy, 1 friendly), rotation to observer(radians), dx, dy, d magnitude (to observer),
    */
    auto baseObs = baseShipObs(ship);

    // float team = ship.getTeam() == observer.getTeam() ? 1.f : -1.f;
    float angle = physics::getRelativeAngle(ship.getCenter(), observer.getCenter(), ship.getRotationCartesian());
    auto dPos = normalizeRelativePos(ship.getCenter() - observer.getCenter());
    auto obs = std::array{normalizeRotation(physics::degreesToRadians(angle)), dPos.x, dPos.y};

    ObservationFactory::RelativeObsType relativeShipObs{};

    std::copy(baseObs.begin(), baseObs.end(), relativeShipObs.begin());
    std::copy(obs.begin(), obs.end(), relativeShipObs.begin() + baseObs.size());
    return relativeShipObs;
}

auto projectileObs(const ships::Ship &observer, const ships::Projectile &proj)
{
    /*
    dx, dy, d magnitude (to observer),
    velocity_x, velocity_y, velocity_magnitude, radius, timespan_left, dmg
    */
    return 1;
}

void embbedShip(int team, int mass, int cpyIndex, ObservationFactory::ObservationType &obs, const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships)
{
    auto findShip = [&](std::shared_ptr<ships::AiShip> ship)
    {
        return (ship->getTeam() == team) && (ship->getMass() == mass);
    };

    auto ship = std::find_if(ships.begin(), ships.end(), findShip);

    if (ship != ships.end())
    {
        auto teammateObs = relativeShipObs(observer, **ship);
        std::copy(teammateObs.begin(), teammateObs.end(), obs.begin() + cpyIndex);
    }
}

ObservationFactory::ObservationType ObservationFactory::makeObservation(const ships::AiShip &observer, const std::vector<std::shared_ptr<ships::AiShip>> &ships)
{
    ObservationType obs{};

    auto observerState = baseShipObs(observer);
    int shipNum = ships.size();
    std::copy(observerState.begin(), observerState.end(), obs.begin());
    int cpyIndex = observerState.size();

    // ONE ORDER - observer, teammate hammerhead, scarab, scarab, hammerhead
    embbedShip(observer.getTeam(), 2500, cpyIndex, obs, observer, ships);
    cpyIndex += relativeObsSize;

    int enemyTeam = observer.getTeam() == config::BLUE_TEAM ? config::RED_TEAM : config::BLUE_TEAM;

    embbedShip(enemyTeam, 1000, cpyIndex, obs, observer, ships);
    cpyIndex += relativeObsSize;

    embbedShip(enemyTeam, 1000, cpyIndex, obs, observer, ships);
    cpyIndex += relativeObsSize;

    embbedShip(enemyTeam, 2500, cpyIndex, obs, observer, ships);
    cpyIndex += relativeObsSize;

    return obs;
}
