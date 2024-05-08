#include "aiShip.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace ships
{
	AiShip::AiShip(const prefabs::ShipPrefab &prefab, int team, sf::Vector2f position, bool neuralNetwork, sf::Vector2f velocity, float rotation) : Ship{prefab, team, position, velocity, rotation}, neuralNetwork{neuralNetwork}
	{
	}
	void AiShip::frameUpdate()
	{
		auto [angle, targetVelocity, shoot, debugShapes] = currentTactic;
		targetAngle = angle;
		accelerationVector = targetVelocity;
		isShooting = shoot;
		Ship::frameUpdate();
		if (neuralNetwork)
			shapesToDraw.push_back(makeCircle(getCenter(), spriteRadius + 20, sf::Color::Magenta));
	}
	void AiShip::determineTactic(const Tactic::Ships &friends, const Tactic::Ships &foes, const Tactic::Collidables &collidables, const Tactic::Projectiles &projectiles)
	{
		if (neuralNetwork)
			return;
		currentTactic = tactic.generateTactic(friends, foes, collidables, projectiles);
	}
	void AiShip::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		Ship::draw(target, states);
		for (auto &shape : currentTactic.debugShapes)
			target.draw(*shape, states);
	}
}