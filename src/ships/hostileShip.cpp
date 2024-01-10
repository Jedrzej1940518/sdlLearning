#include "hostileShip.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>

namespace ships
{
    HostileShip::HostileShip(prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d speed, double rotation)
        : CollisionObject{prefab, position, speed, rotation}
    {
        shipId = uniqueId;
        uniqueId++;
        encircleLeft = uniqueId % 2;
    }
    void HostileShip::determineTactic(const physics::Vector2d &playerPos)
    {

        --tacticTicks;

        if (tacticTicks > 0)
            return;

        tacticTicks = 5;

        double dist = physics::calculateDistance(getObjectCenter(), playerPos);
        tactic = dist > maxPlayerDist ? approach : (dist < avoidanceRadius ? disapproach : encircle);
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
        if (abs(degrees) > 3)
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

    bool HostileShip::avoidCollision(const vector<HostileShip *> &allies, const vector<CollisionObject *> &asteroids, Ship &player)
    {
        bool collisonImminent{false};
        physics::Vector2d avoidanceVector = {0, 0};
        auto pos = getObjectCenter();

        auto avoidPosition = [&](physics::Vector2d position)
        {
            float dist = physics::calculateDistance(pos, position);

            if (dist < avoidanceRadius)
            {
                collisonImminent = true;
                avoidanceVector.x += pos.x - position.x;
                avoidanceVector.y += pos.y - position.y;
            }
        };
        auto avoidPositions = [&]<typename Collidable>(vector<Collidable *> objects)
        {
            for (auto *object : objects)
            {
                if (object == this)
                    continue;
                avoidPosition(object->getObjectCenter());
            };
        };
        avoidPosition(player.getObjectCenter());
        avoidPositions(allies);
        avoidPositions(asteroids);

        if (not collisonImminent)
            return false;

        avoidanceVector = physics::clampVector(avoidanceVector, 1.0);
        double avoidanceAngle = physics::getVectorRotation(avoidanceVector);
        body.accelerateOnce(avoidanceAngle);

        return collisonImminent;
    }

    void HostileShip::renderObject(SDL_Rect viewport)
    {
        CollisionObject::renderObject(viewport);
        if (debugObject)
        {
            auto pos = getObjectCenter() - physics::Vector2d{(double)viewport.x, (double)viewport.y};
            Uint32 color = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 0, 255, 0);
            ellipseColor(gRenderer, pos.x, pos.y, maxPlayerDist, maxPlayerDist, color);

            color = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 255, 0, 0);
            ellipseColor(gRenderer, pos.x, pos.y, avoidanceRadius, avoidanceRadius, color);

            color = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 0, 0, 255);
            lineColor(gRenderer, pos.x, pos.y, pos.x + body.getSpeed().x * 50, pos.y + body.getSpeed().y * 50, color);

            auto accelerationVector = physics::getRotatedVector(getBody().getAccelerationAngle() - 180);
            color = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 0, 255, 255);
            lineColor(gRenderer, pos.x, pos.y, pos.x + accelerationVector.x * 50, pos.y + accelerationVector.y * 50, color);
        }
    }

    Projectile *HostileShip::frameUpdate(const vector<HostileShip *> &allies, const vector<CollisionObject *> &asteroids, Ship &player, CollisionModel &collisionModel)
    {
        allies.size();
        asteroids.size();
        auto pos = player.getObjectCenter();
        CollisionObject::frameUpdate(collisionModel);
        determineTactic(pos);
        determineRotation(pos);
        if (not avoidCollision(allies, asteroids, player))
            determineSpeed(pos);

        if (debugObject)
            print(pos);

        return nullptr;
    }
}