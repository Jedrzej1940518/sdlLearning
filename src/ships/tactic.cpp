#include "tactic.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ships
{
	float calcSafeDist(const Ship& ship)
	{
		const float baseDist = 50.f;
		const float tacticTicks = 20.f;
		return physics::getBrakingDistance(ship.getMaxVelocity(), ship.getMaxAcceleration()) + ship.getMaxVelocity() * tacticTicks + baseDist;
	}
	float calcEncircleRadius(const Ship& ship)
	{
		return ship.getRange();
	}
	Tactic::Tactic(const Ship& guidedShip) : guidedShip{ guidedShip }, safeCollisionDistance{ calcSafeDist(guidedShip) }, encircleRadius{ calcEncircleRadius(guidedShip) }
	{
	}

	sf::Vector2f Tactic::getFleetCenterOfMass(const Ships& friends)
	{
		float totalMass = 0.0;
		float sumWeightedX = 0.0;
		float sumWeightedY = 0.0;

		for (const auto& ship : friends)
		{
			float mass = ship->getMass();
			auto [x, y] = ship->getCenter();

			totalMass += mass;
			sumWeightedX += mass * x;
			sumWeightedY += mass * y;
		}

		sf::Vector2f centerOfMass;
		centerOfMass.x = sumWeightedX / totalMass;
		centerOfMass.y = sumWeightedY / totalMass;

		if (config::debugTactic)
			debugShapes.push_back(makeCircle(centerOfMass, 20 / 2.f, sf::Color::White));

		return centerOfMass;
	}
	const Ship& Tactic::chooseTarget(const Ships& foes, const Ships& friends)
	{
		// in case there's no foes, target will be a fake ship thats veeery far away
		std::reference_wrapper<Ship> target = fakeShip;
		sf::Vector2f fleetCenterOfMass = getFleetCenterOfMass(friends);

		// target is a ship closest to fleet center of mass
		for (const auto& ship : foes)
			if (physics::distance(fleetCenterOfMass, ship->getCollisionCircle()) < physics::distance(fleetCenterOfMass, target.get().getCollisionCircle()))
				target = *ship;

		if (config::debugTactic)
			debugShapes.push_back(makeCircle(target.get().getCenter(), target.get().getRadius() + 5, sf::Color::Cyan));

		return target.get();
	}

	float Tactic::targetAngle(const Ship& target)
	{
		sf::Vector2f relativePos = target.getCenter() - guidedShip.getCenter();
		float targetAngle = physics::getVectorRotation(relativePos);
		return targetAngle;
	}

	sf::Vector2f Tactic::encircleTarget(const Ship& target)
	{
		auto pos = guidedShip.getCenter();
		auto targetPos = target.getCenter();

		float dist = physics::distance(target.getCollisionCircle(), guidedShip.getCollisionCircle());

		sf::Vector2f targetVelocity = physics::clampVector(targetPos - pos, guidedShip.getMaxVelocity());

		if (config::debugTactic)
			debugShapes.push_back(makeCircle(guidedShip.getCenter(), encircleRadius + guidedShip.getRadius(), sf::Color::Green));

		// todo fix
		sf::Transform rotate;
		rotate.rotate(90);
		sf::Vector2f encricleVector = rotate.transformPoint(targetVelocity);

		return dist > encircleRadius ? targetVelocity : encricleVector;
	}

	// x < 1 --> 0
	// x = 1 --> 0
	// x = infinity -> max 
	float proximityFunction(float dist, float safe_dist, float max) {

		dist = dist > 0.01f ? dist : 0.01f;
		float x = safe_dist / dist;
		float modified_sigmoid = (1. / (1. + exp(-x + 1))) * 2.f - 1.f;
		return  std::clamp(modified_sigmoid * max, 0.f, max);
	}

	// Vector Field Histogram algorithm
	sf::Vector2f Tactic::avoidCollisions(sf::Vector2f velocity, const Collidables& collidables, const Projectiles& projectiles)
	{
		if (config::debugTactic) {
			auto [arrowBase, arrowPoint] = getVectorShapes(velocity, guidedShip.getCenter(), sf::Color::Magenta);

			debugShapes.push_back(std::move(arrowBase));
			debugShapes.push_back(std::move(arrowPoint));
			debugShapes.push_back(makeCircle(guidedShip.getCenter(), safeCollisionDistance + guidedShip.getRadius(), sf::Color::Red));
			//LOG("[%s] Base velocity [%f %f]\n", guidedShip.getId().c_str(), velocity.x, velocity.y);
		}


		auto avoidCollisions = [&]<typename Vec>(const Vec & collidables)
		{
			for (const auto& object : collidables)
			{
				//todo optimize, ugly, why?
				if (object->getId() == guidedShip.getId())
					continue;

				float dist = physics::distance(object->getCollisionCircle(), guidedShip.getCollisionCircle());

				if (dist < safeCollisionDistance)
				{
					sf::Vector2f deltaVector = physics::clampVector(object->getCenter() - guidedShip.getCenter(), 1.0f);
					float angle = physics::getAngleBetweenVectors(velocity, deltaVector);
					//LOG("%s | angle [%f] velocity [%f %f], deltaVector [%f %f]", object->getId().c_str(), angle, velocity.x, velocity.y, deltaVector.x, deltaVector.y);
					// If the obstacle is in front of the ship, adjust the velocity vector
					if (fabs(angle) < 90.f)
					{
						float max = guidedShip.getMaxVelocity() * 2;
						float scale = proximityFunction(dist, safeCollisionDistance, max);
						deltaVector *= scale;
						velocity -= deltaVector;

						if (config::debugTactic) {
							auto [arrowBase, arrowPoint] = getVectorShapes(-deltaVector, guidedShip.getCenter(), sf::Color::Red);

							debugShapes.push_back(std::move(arrowBase));
							debugShapes.push_back(std::move(arrowPoint));
						}
						//LOG(" dist [%f], proximity [%f], deltaVectorScaled [%f %f], \n",  dist, proximityFunction(dist, safeCollisionDistance, max),  deltaVector.x, deltaVector.y);
					}
				}
			}
		};

		avoidCollisions(collidables);
		avoidCollisions(projectiles);
		velocity = physics::clampVector(velocity, guidedShip.getMaxVelocity());

		if (config::debugTactic) {
			auto [arrowBase, arrowPoint] = getVectorShapes(velocity, guidedShip.getCenter(), sf::Color::Yellow);

			debugShapes.push_back(std::move(arrowBase));
			debugShapes.push_back(std::move(arrowPoint));
		}

		return velocity;
	}
	bool Tactic::shouldShoot(const Ship& target, const Ships& friends)
	{
		float angleToTarget = physics::getAngleBetweenVectors(physics::getRotatedVector(guidedShip.getRotationCartesian()), target.getCenter());
		bool inRange = physics::distance(guidedShip.getCollisionCircle(), target.getCollisionCircle()) < guidedShip.getRange();

		const auto& weapon = guidedShip.getWeapon();
		auto projectilePos = weapon.getProjectileSpawnPoint(guidedShip.getRotationCartesian(), guidedShip.getCenter());
		auto projectileVelocity = weapon.getProjectileVelocity(guidedShip.getRotationCartesian());
		float projectileSpeed = weapon.getMaxVelocity();

		float rectW = projectileSpeed * 30.f;
		float rectH = projectileSpeed * 5.f;

		bool shouldShoot = inRange && angleToTarget < 3.f;

		sf::Transform r;
		sf::FloatRect shotPath{ {0.f,0.f}, sf::Vector2f{rectW, rectH } };
		shotPath = r.rotate(guidedShip.getRotationCartesian(), projectilePos).translate(projectilePos - sf::Vector2f{ 0.f, rectH / 2.f }).transformRect(shotPath);

		for (const auto& ship : friends)
		{
			if (ship->getId() == guidedShip.getId())
				continue;

			//if friendly fire then shouldnt shoot
			shouldShoot &= (not shotPath.intersects(ship->getBoundingBox()));
		}


		if (config::debugTactic) {
			auto rect = makeRectangle({ rectW, rectH }, sf::Color::Magenta);
			rect->setOrigin({ 0, rectH / 2.f });
			rect->setPosition(projectilePos);
			rect->rotate(guidedShip.getRotationCartesian());
			debugShapes.push_back(rect);
		}
		return shouldShoot;
	}

	Tactic::TacticOutcome Tactic::generateTactic(const Ships& friends, const Ships& foes, const Collidables& collidables, const Projectiles& projectiles)
	{
		debugShapes.clear();
		const Ship& target = chooseTarget(foes, friends);
		sf::Vector2f velocity = encircleTarget(target);
		velocity = avoidCollisions(velocity, collidables, projectiles);
		float angle = targetAngle(target);
		bool shoot = shouldShoot(target, friends);
		return { angle, velocity, shoot, debugShapes };
	}

}