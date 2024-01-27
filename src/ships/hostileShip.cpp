#include "hostileShip.hpp"

// #include <SDL2/SDL2_gfxPrimitives.h>

namespace ships
{
    HostileShip::HostileShip(const prefabs::Prefab &prefab, const prefabs::ProjectilePrefab &projectilePrefab, physics::Vector2d position, physics::Vector2d velocity, double rotation)
        : CollisionObject{prefab, position, velocity, rotation}, projectilePrefab{projectilePrefab}
    {
        shipId = uniqueId;
        uniqueId++;
        encircleLeft = uniqueId % 2;
        avoidanceRadius = 250;
        avoidanceRadius += radius;
    }
    void HostileShip::determineTactic(const physics::Vector2d &playerPos)
    {

        --tacticTicks;

        if (tacticTicks > 0)
            return;

        tacticTicks = 1;

        double dist = physics::calculateDistance(getObjectCenter(), playerPos);
        tactic = dist > maxPlayerDist ? approach : (dist < avoidanceRadius ? disapproach : encircle);
    }
    double HostileShip::determineLookAngle(const Ship &player)
    {
        physics::Vector2d playerPos = player.getObjectCenter();
        physics::Vector2d translated = playerPos - getObjectCenter();

        int ticks = physics::calculateTicks(translated, projectilePrefab.hardware.maxVelocity);
        physics::Vector2d predictedPos = physics::predictPosition(translated, player.getBody().getSpeed(), ticks);

        double playerRotation = physics::normalizeDegrees(physics::getVectorRotation(predictedPos) + 90);
        double angle = getRotation() - playerRotation;
        angle = angle > 360 ? angle - 360 : (angle < 0 ? angle + 360 : angle);
        playerOnLeft = angle < 180;
        return angle;
    }
    void HostileShip::determineRotation(const Ship &player)
    {
        double degrees = 0;

        if (rotationTicks <= 0)
        {
            degrees = determineLookAngle(player);
            body.rotate(0);
        }
        if (abs(degrees) > 3)
        {
            rotationTicks = 1;
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

        printf("HS[%d] Dist %f Tactic: %s, acceleration_angle: %f, velocity [%f, %f]\n", shipId, physics::calculateDistance(getObjectCenter(), playerPos), s.c_str(), body.getAccelerationAngle(), body.getSpeed().x, body.getSpeed().y);
    }

    bool HostileShip::avoidCollision(const vector<HostileShip *> &allies, const vector<CollisionObject *> &asteroids, const Ship &player)
    {
        bool collisonImminent{false};
        physics::Vector2d avoidanceVector = {0, 0};
        auto pos = getObjectCenter();

        auto avoidPosition = [&](physics::Vector2d position, int othObjRadius)
        {
            double dist = physics::calculateDistance(pos, position) - othObjRadius;

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
                avoidPosition(object->getObjectCenter(), object->getRadius());
            };
        };
        avoidPosition(player.getObjectCenter(), player.getRadius());
        avoidPositions(allies);
        avoidPositions(asteroids);

        if (not collisonImminent)
            return false;

        avoidanceVector = physics::clampVector(avoidanceVector, 1.0);
        double avoidanceAngle = physics::getVectorRotation(avoidanceVector);
        body.accelerateOnce(avoidanceAngle + 90);

        return collisonImminent;
    }
    void HostileShip::debugRender(SDL_Rect viewport)
    {
        // auto pos = getObjectCenter() - physics::Vector2d{(double)viewport.x, (double)viewport.y};
        // Uint32 color = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 0, 255, 0);
        // ellipseColor(gRenderer, pos.x, pos.y, maxPlayerDist, maxPlayerDist, color);

        // color = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 255, 0, 0);
        // ellipseColor(gRenderer, pos.x, pos.y, avoidanceRadius, avoidanceRadius, color);
    }
    void HostileShip::renderObject(SDL_Rect viewport)
    {
        CollisionObject::renderObject(viewport);
        if (debugObject)
            debugRender(viewport);
    }

    Projectile *HostileShip::shoot(const physics::Vector2d &playerPos)
    {
        reloadTicks = std::max(reloadTicks - 1, 0);
        Projectile *p = nullptr;
        if (reloadTicks > 0)
            return p;

        auto dist = physics::calculateDistance(playerPos, getObjectCenter());
        auto maxRange = projectilePrefab.lifetime * projectilePrefab.hardware.maxVelocity;

        if (dist < maxRange && (abs(body.getRotationLeft()) < 15 || abs(body.getRotationLeft()) > 345))
        {
            p = Projectile::spawnProjectile(projectilePrefab, *this);
            reloadTicks = projectilePrefab.reload;
        }
        return p;
    }
    Projectile *HostileShip::frameUpdate(const vector<HostileShip *> &allies, const vector<CollisionObject *> &asteroids, const Ship &player, CollisionModel &collisionModel)
    {
        auto pos = player.getObjectCenter();
        CollisionObject::frameUpdate(collisionModel);
        determineTactic(pos);
        determineRotation(player);

        if (not avoidCollision(allies, asteroids, player))
            determineSpeed(pos);

        Projectile *p = shoot(pos);

        if (debugObject)
            print(pos);

        return p;
    }
}