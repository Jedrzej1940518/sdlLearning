#include "hostileShip.hpp"

namespace ships
{
    HostileShip::HostileShip(prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d speed, double rotation)
        : CollisionObject{prefab, position, speed, rotation}
    {
    }
    double HostileShip::determineLookAngle(physics::Vector2d playerPos)
    {
        auto translated = playerPos - getPosition();
        double playerRotation = physics::normalizeDegrees(physics::getVectorRotation(translated) + 90);
        double angle = getRotation() - playerRotation;
        angle = angle > 360 ? angle - 360 : (angle < 0 ? angle + 360 : angle);
        playerOnLeft = angle < 180;
        return angle;
    }
    void HostileShip::determineRotation(const physics::Vector2d &playerPos)
    {
        double degrees = 0;

        if (rotationTicks <= 0)
        {
            degrees = determineLookAngle(playerPos);
            body.rotate(0);
        }
        if (abs(degrees) > 15)
        {
            rotationTicks = 5;
            body.rotate(playerOnLeft ? -abs(degrees) : abs(degrees));
        }

        --rotationTicks;
    }

    void HostileShip::determineSpeed(const physics::Vector2d &playerPos)
    {
        constexpr int maxPlayerDist = 600;
        auto playerShipAngle = physics::normalizeDegrees(physics::getAngleBetweenPoints(getPosition(), playerPos) + 90);
        double accelerationDir = tactic == approach ? playerShipAngle : -playerShipAngle;
        body.accelerateOnce(accelerationDir);
        --tacticTicks;

        if (tacticTicks > 0)
            return;

        tacticTicks = 5;

        double dist = physics::calculateDistance(getPosition(), playerPos);
        tactic = dist > maxPlayerDist ? approach : disapproach;
    }

    Projectile *HostileShip::frameUpdate(const vector<HostileShip *> & /*allies*/, Ship &player)
    {
        determineRotation(player.getPosition());
        determineSpeed(player.getPosition());
        return nullptr;
    }

}