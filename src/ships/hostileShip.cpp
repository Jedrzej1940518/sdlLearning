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
        LOG("left? %u, player %lf, rotation %lf, angle %lf", playerOnLeft, playerRotation, getRotation(), angle);
        return angle;
        // auto rotationVector = physics::getRotatedVector(rotation);
    }
    Projectile *HostileShip::frameUpdate(const vector<HostileShip *> & /*allies*/, Ship &player)
    {
        //  constexpr double minPlayerDist = 200;
        // constexpr double maxPlayerDist = 600;

        enum Tactic
        {
            approach,
            disapproach
        };
        // double dist = physics::calculateDistance(position, player.getPosition());
        // Tactic tactic = dist > maxPlayerDist ? approach : disapproach;
        // auto rotatedVector = physics::getRotatedVector(getRotation());
        double degrees = 0;

        if (rotationTicks <= 0)
        {
            degrees = determineLookAngle(player.getPosition());
            body.rotate(0);
        }
        if (abs(degrees) > 15)
        {
            // degrees = degrees > 180 ? degrees - 360 : degrees;
            // degrees = degrees < -180 ? degrees + 360 : degrees;
            // LOG("degrees %lf", degrees);
            rotationTicks = 5;
            body.rotate(playerOnLeft ? -abs(degrees) : abs(degrees));
        }

        --rotationTicks;
        // LOG("tatctic %d distance = %lf, degrees = %lf, rv [%lf %lf]", (int)tactic, dist, degrees, rotatedVector.x, rotatedVector.y);
        return nullptr;
    }
}