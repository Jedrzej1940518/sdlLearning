#include "tactic.hpp"

namespace ships
{
    float calcSafeDist(const Ship &ship)
    {
        return physics::getBrakingDistance(ship.getMaxVelocity() * 1.5f, ship.getMaxAcceleration());
    }
    float calcEncircleRadius(const Ship &ship)
    {
        return 500.f; // todo calc range
    }
    Tactic::Tactic(const Ship &guidedShip) : guidedShip{guidedShip}, safeCollisionDistance{calcSafeDist(guidedShip)}, encircleRadius{calcEncircleRadius(guidedShip)}
    {
    }

    sf::Vector2f Tactic::getFleetCenterOfMass(const Ships &friends)
    {
        float totalMass = 0.0;
        float sumWeightedX = 0.0;
        float sumWeightedY = 0.0;

        for (const auto &ship : friends)
        {
            float mass = ship->getMass();
            auto [x, y] = ship->getCenter();

            printf("x %f y %f <= [%f, %f] \n", x, y, ship->getCenter().x, ship->getCenter().y);
            totalMass += mass;
            sumWeightedX += mass * x;
            sumWeightedY += mass * y;
        }

        sf::Vector2f centerOfMass;
        centerOfMass.x = sumWeightedX / totalMass;
        centerOfMass.y = sumWeightedY / totalMass;

        return centerOfMass;
    }
    const Ship &Tactic::chooseTarget(const Ships &foes, const Ships &friends)
    {
        // in case there's no foes, target will be a fake ship thats veeery far away
        std::reference_wrapper<Ship> target = fakeShip;
        sf::Vector2f fleetCenterOfMass = getFleetCenterOfMass(friends);

        // target is a ship closest to fleet center of mass
        for (const auto &ship : foes)
            if (physics::distance(fleetCenterOfMass, ship->getCenter()) < physics::distance(fleetCenterOfMass, target.get().getCenter()))
                target = *ship;

        return target.get();
    }

    float Tactic::targetAngle(const Ship &target)
    {
        sf::Vector2f relativePos = target.getCenter() - guidedShip.getCenter();
        float targetAngle = physics::getVectorRotation(relativePos);
        return targetAngle;
    }

    sf::Vector2f Tactic::encircleTarget(const Ship &target)
    {
        auto pos = guidedShip.getCenter();
        auto targetPos = target.getCenter();

        float dist = physics::distance(targetPos, pos) - target.getRadius() - guidedShip.getRadius();

        sf::Vector2f targetVelocity = physics::clampVector(targetPos - pos, guidedShip.getMaxVelocity());
        // todo fix
        return dist > encircleRadius ? targetVelocity : -targetVelocity;
    }

    // Vector Field Histogram algorithm
    sf::Vector2f Tactic::avoidCollisions(sf::Vector2f velocity, const Collidables &collidables, const Projectiles &projectiles)
    {
        auto avoidCollisions = [&]<typename Vec>(const Vec &collidables)
        {
        for (const auto &object : collidables)
        {
            sf::Vector2f objPos = object->getCenter();
            sf::Vector2f shipPos = guidedShip.getCenter();

            float dist = physics::distance(shipPos, objPos);

            if (dist < safeCollisionDistance + object->getRadius())
            {
                sf::Vector2f deltaVector = objPos - shipPos;
                float angle = physics::getAngleBetweenVectors(velocity, deltaVector);

                // If the obstacle is in front of the ship, adjust the velocity vector
                if (fabs(angle) < 90.f)
                {
                    float scale = (safeCollisionDistance + object->getRadius() - dist) / (safeCollisionDistance + object->getRadius());
                    deltaVector *= scale;
                    velocity += deltaVector;
                }
            }
        } };

        avoidCollisions(collidables);
        avoidCollisions(projectiles);

        return velocity;
    }

    Tactic::TacticOutcome Tactic::generateTactic(const Ships &friends, const Ships &foes, const Collidables &collidables, const Projectiles &projectiles)
    {
        const Ship &target = chooseTarget(foes, friends);
        sf::Vector2f velocity = encircleTarget(target);
        velocity = avoidCollisions(velocity, collidables, projectiles);
        float angle = targetAngle(target);
        return {angle, velocity, false};
    }

}