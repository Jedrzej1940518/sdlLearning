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
		std::vector<std::shared_ptr<sf::Shape>> debugShapes;

		const Ship &guidedShip;
		// this is distance between edges of objects, so it takes into account objects radius
		const float safeCollisionDistance;

	public:
		typedef std::vector<std::shared_ptr<Ship>> Ships;
		typedef std::vector<std::shared_ptr<rendering::CollisionObject>> Collidables;
		typedef std::vector<std::shared_ptr<Projectile>> Projectiles;

		struct TacticOutcome
		{
			float targetAngle;
			sf::Vector2f targetVelocity;
			bool shoot;
			std::vector<std::shared_ptr<sf::Shape>> debugShapes;
		};
		Tactic(const Ship &guidedShip);

		TacticOutcome generateTactic(const Ships &friends, const Ships &foes, const Collidables &collidables, const Projectiles &projectiles);

	private:
		const Ship &chooseTarget(const Ships &foes, const Ships &friends);
		sf::Vector2f getFleetCenterOfMass(const Ships &friends);

		sf::Vector2f encircleTarget(const Ship &target);
		float calcEncircleDist(const Ship &target);
		sf::Vector2f avoidCollisions(sf::Vector2f velocity, const Collidables &collidables, const Projectiles &projectiles);

		bool noFriendlyFire(const Ships &friends);

		float getProjectileInterceptTime(const sf::Vector2f &target, const sf::Vector2f &targetVelocity, float targetRadius);
		float tExtra(float targetRadius);
		float targetAngle(const sf::Vector2f &target, const sf::Vector2f &targetVelocity, float targetRadius, float ticks);
		sf::Vector2f predictShotNeededPosition(const Ship &target);
		bool inRange(const Ship &target);
	};

}