#pragma once

#include "ship.hpp"
#include "tactic.hpp"

namespace ships
{
    class AiShip : public Ship
    {
        Tactic tactic{*this};
        Tactic::TacticOutcome currentTactic;

    public:
        AiShip(const prefabs::ShipPrefab &prefab, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, float rotation = 0);
        void frameUpdate() override;
        void determineTactic(const Tactic::Ships &friends, const Tactic::Ships &foes, const Tactic::Collidables &collidables, const Tactic::Projectiles &projectiles);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        virtual ~AiShip() {}
    };
}