#pragma once

#include "ship.hpp"
#include "tactic.hpp"

namespace ships
{
    class AiShip : public Ship
    {
        Tactic tactic{*this};
        Tactic::TacticOutcome currentTactic;
        bool neuralNetwork = false;

    public:
        AiShip(const prefabs::ShipPrefab &prefab, int team, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, float rotation = 0, bool neuralNetwork = false);
        void frameUpdate() override;
        void determineTactic(const Tactic::Ships &friends, const Tactic::Ships &foes, const Tactic::Collidables &collidables, const Tactic::Projectiles &projectiles);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void setTactic(Tactic::TacticOutcome newTactic) { currentTactic = newTactic; }
        bool isNeuralNetwork() const { return neuralNetwork; }

        virtual ~AiShip() {}
    };
}