#include "aiShip.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace ships
{
	AiShip::AiShip(const prefabs::ShipPrefab &prefab, sf::Vector2f position, sf::Vector2f velocity, float rotation, bool neuralNetwork) : Ship{prefab, position, velocity, rotation}, neuralNetwork{neuralNetwork}
	{
	}
	void AiShip::frameUpdate()
	{
		auto [angle, targetVelocity, shoot, debugShapes] = currentTactic;
		targetAngle = angle;
		accelerationVector = targetVelocity;
		isShooting = shoot;
		Ship::frameUpdate();
	}
	void AiShip::determineTactic(const Tactic::Ships &friends, const Tactic::Ships &foes, const Tactic::Collidables &collidables, const Tactic::Projectiles &projectiles)
	{
		if (neuralNetwork)
			return;
		currentTactic = tactic.generateTactic(friends, foes, collidables, projectiles);
		std::cout << "determining tactic " << currentTactic.shoot << " " << currentTactic.targetAngle << " " << currentTactic.targetVelocity.x << " " << currentTactic.targetVelocity.y << std::endl;
	}
	void AiShip::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		Ship::draw(target, states);
		for (auto &shape : currentTactic.debugShapes)
			target.draw(*shape, states);
	}
}