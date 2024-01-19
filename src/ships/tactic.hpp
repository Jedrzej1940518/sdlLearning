#pragma once

#include "ship.hpp"
#include "projectile.hpp"
#include "prefabs/prefabs.hpp"

#include <vector>
#include <memory>

#include <SFML/System/Vector2.hpp>

namespace ships
{
    class Tactic
    {
    private:
        // fake target in case no foes are present
        inline static Ship fakeShip{prefabs::scarab, {std::numeric_limits<float>::max() / 4.f, std::numeric_limits<float>::max() / 4.f}};

        inline static constexpr bool debug{true};
        // std::vector<std::unique_ptr<sf::Shape>> debugShapes;

        const Ship &guidedShip;
        // TODO this should be different for each enemy ship but whatever
        const float safeCollisionDistance;
        const float encircleRadius;

    public:
        typedef std::vector<std::shared_ptr<Ship>> Ships;
        typedef std::vector<std::shared_ptr<rendering::CollisionObject>> Collidables;
        typedef std::vector<std::shared_ptr<Projectile>> Projectiles;

        struct TacticOutcome
        {
            float targetAngle;
            sf::Vector2f targetVelocity;
            bool shoot;
        };
        Tactic(const Ship &guidedShip);

        TacticOutcome generateTactic(const Ships &friends, const Ships &foes, const Collidables &collidables, const Projectiles &projectiles);

    private:
        sf::Vector2f getFleetCenterOfMass(const Ships &friends);
        const Ship &chooseTarget(const Ships &foes, const Ships &friends);
        sf::Vector2f encircleTarget(const Ship &target);
        sf::Vector2f avoidCollisions(sf::Vector2f velocity, const Collidables &collidables, const Projectiles &projectiles);
        float targetAngle(const Ship &target);
    };

}