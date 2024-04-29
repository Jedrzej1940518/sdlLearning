
#include "observationFactory.hpp"

float normalizePos(float x)
{
    return std::clamp(x / 5000, -1.f, 1.f);
}

float normalizeVelocity(float x)
{
    return std::clamp(x / 6, -1.f, 1.f);
}

float normalizeHp(float hp)
{
    return std::clamp(hp / 300, 0.f, 1.f);
}

float normalizeAcceleration(float maxAcceleration)
{
    return std::clamp(maxAcceleration / 1, 0.f, 1.f);
}

float normalizeRotation(float radians)
{
    return std::clamp(radians / 6.28f, -1.f, 1.f);
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
    return std::clamp(projVelocity / 10, 0.f, 1.f);
}

float normalizeProjLifetime(float projLifetime)
{
    return std::clamp(projLifetime / 40, 0.f, 1.f);
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
    const auto &w = ship.getWeapon();
    return ObservationFactory::BaseObsType{
        normalizePos(ship.getCenter().x),
        normalizePos(ship.getCenter().y),
        normalizeVelocity(ship.getVelocity().x),
        normalizeVelocity(ship.getVelocity().y),
        normalizeVelocity(physics::getVectorMagnitude(ship.getVelocity())),
        normalizeHp((float)ship.getHp()),
        normalizeVelocity(ship.getMaxVelocity()),
        normalizeAcceleration(ship.getMaxAcceleration()),
        normalizeRotation(physics::degreesToRadians(ship.getRotationCartesian())),
        normalizeShipRadius(ship.getRadius()),
        ship.getCooldown() / ship.getMaxCooldown(),
        normalizeCooldown(ship.getMaxCooldown()),
        normalizeProjVelocity(w.getMaxVelocity()),
        normalizeProjLifetime((float)w.getLifetime()),
        normalizeProjDmg((float)w.getDmg()),
        normalizeProjScatter(w.getScatter())};
}

ObservationFactory::RelativeObsType relativeShipObs(const ships::Ship &observer, const ships::Ship &ship)
{
    /*
    baseShipObs,
    team (-1 enemy, 1 friendly), rotation to observer(radians), dx, dy, d magnitude (to observer),
    */
    auto baseObs = baseShipObs(ship);

    float team = ship.getTeam() == observer.getTeam() ? 1.f : -1.f;
    float angle = physics::getRelativeAngle(ship.getCenter(), observer.getCenter(), ship.getRotationCartesian());
    auto dPos = normalizeRelativePos(ship.getCenter() - observer.getCenter());
    auto obs = std::array{
        team, normalizeRotation(physics::degreesToRadians(angle)), dPos.x, dPos.y, physics::getVectorMagnitude(dPos)};

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

ObservationFactory::ObservationType ObservationFactory::makeObservation(const ships::Ship &observer, const std::vector<std::shared_ptr<ships::Ship>> &ships)
{

    ObservationType obs{};
    auto observerState = baseShipObs(observer);
    int embeddedObs = 0;
    int shipNum = ships.size();
    std::copy(observerState.begin(), observerState.end(), obs.begin());
    int cpyIndex = observerState.size();
    // embedding alive ships
    for (int i = 0; i < shipNum; ++i)
    {
        auto &ship = *(ships[i]);

        if (ship.getShipId() == observer.getShipId())
            continue;

        auto shipObs = relativeShipObs(observer, ship);
        std::copy(shipObs.begin(), shipObs.end(), obs.begin() + cpyIndex);
        cpyIndex += shipObs.size();
    }
    // rest of observation is empty

    return obs;
}

/*
        if (hostileShips.size() == 0)
            return ObservationType{};

        auto vel = neuralNetworkShip->getVelocity();
        auto velNormalized = vel / neuralNetworkShip->getMaxVelocity();

        auto relativePos = neuralNetworkShip->getCenter() - hostileShips[0]->getCenter();
        auto rposNorm = relativePos / 10000.f; // damn thats big
        auto hostileVel = hostileShips[0]->getVelocity() / hostileShips[0]->getMaxVelocity();
        auto obs = ObservationType{
            rposNorm.x, rposNorm.y,
            hostileVel.x, hostileVel.y,
            velNormalized.x, velNormalized.y,
            neuralNetworkShip->getRotationCartesian() / 360,
            neuralNetworkShip->getCooldown() / neuralNetworkShip->getMaxCooldown()};

        return obs;

    */