#include "aiShip.hpp"

namespace ships
{
    AiShip::AiShip(const prefabs::ShipPrefab &prefab, sf::Vector2f position, sf::Vector2f velocity, float rotation) : Ship{prefab, position, velocity, rotation}
    {
    }
    void AiShip::frameUpdate()
    {
        auto [angle, targetVelocity, shoot] = currentTactic;
        targetAngle = angle;
        accelerationVector = targetVelocity;

        Ship::frameUpdate();
    }
    void AiShip::determineTactic(const Tactic::Ships &friends, const Tactic::Ships &foes, const Tactic::Collidables &collidables, const Tactic::Projectiles &projectiles)
    {
        static int tacticTicks = 20;
        --tacticTicks;
        if (tacticTicks >= 0)
            return;

        tacticTicks = 10;
        currentTactic = tactic.generateTactic(friends, foes, collidables, projectiles);
    }
}