#include "hostileShip.hpp"

namespace ships
{
    HostileShip::HostileShip(prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d speed, double rotation)
        : CollisionObject{prefab, position, speed, rotation}
    {
        shipId = uniqueId;
        uniqueId++;
        encircleLeft = true;
    }
    void HostileShip::determineTactic(const physics::Vector2d &playerPos)
    {
        constexpr int minPlayerDist = 200;
        constexpr int maxPlayerDist = 400;

        --tacticTicks;

        if (tacticTicks > 0)
            return;

        tacticTicks = 5;

        double dist = physics::calculateDistance(getObjectCenter(), playerPos);
        tactic = dist > maxPlayerDist ? approach : (dist < minPlayerDist ? disapproach : encircle);
    }
    double HostileShip::determineLookAngle(physics::Vector2d playerPos)
    {
        auto translated = playerPos - getObjectCenter();
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
        auto playerShipAngle = physics::normalizeDegrees(physics::getAngleBetweenPoints(getObjectCenter(), playerPos) + 90);
        double accelerationDir = 0;
        switch (tactic)
        {
        case approach:
            accelerationDir = playerShipAngle;
            break;
        case disapproach:
            accelerationDir = -playerShipAngle;
            break;
        case encircle:
            accelerationDir = playerShipAngle + (encircleLeft ? 90 : -90);
            break;
        default:
            break;
        }
        body.accelerateOnce(accelerationDir);
    }

    void HostileShip::print(const physics::Vector2d &playerPos)
    {
        string s = "";
        switch (tactic)
        {
        case approach:
            s = "approach";
            break;
        case disapproach:
            s = "disapproach";
            break;
        case encircle:
            s = "encircle";
            break;
        default:
            break;
        }

        printf("HS[%d] Dist %f Tactic: %s, acceleration_angle: %f, speed [%f, %f]\n", shipId, physics::calculateDistance(getObjectCenter(), playerPos), s.c_str(), body.getAccelerationAngle(), body.getSpeed().x, body.getSpeed().y);
    }
    Projectile *HostileShip::frameUpdate(const vector<HostileShip *> &allies, const vector<CollisionObject *> &asteroids, Ship &player, CollisionModel &collisionModel)
    {
        allies.size();
        asteroids.size();
        auto pos = player.getObjectCenter();
        CollisionObject::frameUpdate(collisionModel);
        determineTactic(pos);
        // determineRotation(pos);
        determineSpeed(pos);
        //  print(pos);
        return nullptr;
    }

}