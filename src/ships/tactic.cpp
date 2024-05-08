#include "tactic.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ships
{

	float calcSafeDist(const Ship &ship)
	{
		return physics::getBrakingDistance(ship.getMaxVelocity(), ship.getMaxAcceleration()) + constants::BASE_SAFE_DIST;
	}

	// x <= 1 --> 0
	// x = infinity -> max
	float modifiedSigmoid(float x, float max)
	{

		float translatedSigmoid = (1.f / (1.f + exp(-x + 1))) * 2.f - 1.f;
		return std::clamp(translatedSigmoid * max, 0.f, max);
	}

	Tactic::Tactic(const Ship &guidedShip) : guidedShip{guidedShip}, safeCollisionDistance{calcSafeDist(guidedShip)}
	{
	}

	sf::Vector2f Tactic::getFleetCenterOfMass(const Ships &friends)
	{
		float totalMass = 0.0;
		float sumWeightedX = 0.0;
		float sumWeightedY = 0.0;

		for (const auto &ship : friends)
		{
			float mass = ship->getMass();
			auto &[x, y] = ship->getCenter();

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
	const Ship &Tactic::chooseTarget(const Ships &foes, const Ships &friends)
	{
		// in case there's no foes, target will be a fake ship thats veeery far away
		std::reference_wrapper<Ship> target = fakeShip;
		sf::Vector2f fleetCenterOfMass = getFleetCenterOfMass(friends);

		// target is a ship closest to fleet center of mass
		for (const auto &ship : foes)
			if (physics::distance(fleetCenterOfMass, ship->getCollisionCircle()) < physics::distance(fleetCenterOfMass, target.get().getCollisionCircle()))
				target = *ship;

		if (config::debugTactic)
			debugShapes.push_back(makeCircle(target.get().getCenter(), target.get().getRadius() + 5, sf::Color::Cyan));

		return target.get();
	}

	sf::Vector2f Tactic::predictShotNeededPosition(const Ship &target)
	{
		// LOG("0\n");
		return {0, 0};
	}

	// |vs|^2 - (vr.x ^2 + vr.y^2) cant be zero i think

	bool Tactic::inRange(const Ship &target)
	{
		// LOG("0\n");
		return true;
	}

	// this is done equation
	//  |Vp| * t = |(Dab + Vrel * t)| <- magnitude of distance between ship and target is equal to magnitude of projectile speed * t
	//  square this, simplyfy and we get the solution
	float Tactic::getProjectileInterceptTime(const sf::Vector2f &target, const sf::Vector2f &targetVelocity, float targetRadius)
	{
		auto &weapon = guidedShip.getWeapon();

		sf::Vector2f vRel = targetVelocity - guidedShip.getVelocity();
		float vP = weapon.getMaxVelocity();

		auto dAB = target - guidedShip.getCenter();

		// we substract various circle radiuses to achieve true distance
		auto rotation = physics::getVectorRotation(dAB);
		float rs = targetRadius + guidedShip.getRadius() + guidedShip.getWeapon().getProjectileRadius() * 2.f;
		auto vecRs = physics::getRotatedVector(rotation) * rs;
		dAB = dAB - vecRs;

		float a = physics::getVectorsDotProduct(vRel, vRel) - (vP * vP);
		float b = 2.f * (physics::getVectorsDotProduct(vRel, dAB));
		float c = physics::getVectorsDotProduct(dAB, dAB);

		float delta = (float)pow(b, 2) - (4.f * a * c);
		if (delta < 0)
		{
			// LOG("no intercept possible, delta < 0, a%.2f b%.2f c%.2f", a, b, c);
			return 1000000.f;
		}
		if (physics::isZero(a))
		{
			// LOG("a == 0, linear problem");
			return 1000000.f;
		}
		float sqrtDelta = sqrt(delta);
		float t1 = (-b + sqrtDelta) / (2.f * a);
		float t2 = (-b - (sqrtDelta)) / (2.f * a);
		float t = t1 > 0.f && t2 > 0.f ? std::min(t1, t2) : (t1 > 0.f ? t1 : t2);

		// t might be <0 or very big
		return t;
	}

	// this makes it so we shoot even if target center is not in range, just part of his body
	float Tactic::tExtra(float targetRadius)
	{
		return targetRadius / guidedShip.getWeapon().getMaxVelocity();
	}

	float Tactic::targetAngle(const sf::Vector2f &target, const sf::Vector2f &targetVelocity, float targetRadius, float ticks)
	{

		float t_norm = std::clamp(ticks, 0.1f, (float)guidedShip.getWeapon().getLifetime() + tExtra(targetRadius));

		auto pbFuture = target + targetVelocity * t_norm;
		auto relativeShipPos = (pbFuture - (guidedShip.getCenter() + guidedShip.getVelocity() * ticks));

		auto pVelocity = relativeShipPos / t_norm;
		float targetAngle = physics::getVectorRotation(pVelocity);

		if (config::debugTactic)
		{
			debugShapes.push_back(makeCircle(pbFuture, 5, sf::Color::Blue));
			auto [arrowBase, arrowPoint] = getVectorShapes(pVelocity, guidedShip.getCenter(), sf::Color::Yellow, 1);

			debugShapes.push_back(std::move(arrowBase));
			debugShapes.push_back(std::move(arrowPoint));
		}
		return targetAngle;
	}

	sf::Vector2f Tactic::encircleTarget(const Ship &target)
	{
		float maxEncircleDist = calcEncircleDist(target);
		float minEncircleDist = maxEncircleDist - constants::BASE_SAFE_DIST;

		auto &pos = guidedShip.getCenter();
		auto &targetPos = target.getCenter();

		float dist = physics::distance(target.getCollisionCircle(), guidedShip.getCollisionCircle());

		sf::Vector2f targetVelocity = physics::clampVector(targetPos - pos, guidedShip.getMaxVelocity());

		float d = dist - minEncircleDist;
		d = physics::isZero(d) ? 0.1f : d;
		float x = constants::BASE_SAFE_DIST / d;
		// todo fix
		sf::Transform rotate;
		rotate.rotate(modifiedSigmoid(x, 90.f));
		sf::Vector2f encricleVector = rotate.transformPoint(targetVelocity);

		if (config::debugTactic)
		{
			debugShapes.push_back(makeCircle(guidedShip.getCenter(), minEncircleDist + guidedShip.getRadius(), {255, 123, 123}));
			debugShapes.push_back(makeCircle(guidedShip.getCenter(), maxEncircleDist + guidedShip.getRadius(), sf::Color::Green));
		}

		return dist > maxEncircleDist ? targetVelocity : (dist < minEncircleDist ? -targetVelocity : encricleVector);
	}

	float Tactic::calcEncircleDist(const Ship &target)
	{
		float relativeSpeed = target.getMaxVelocity() - guidedShip.getMaxVelocity() - guidedShip.getWeapon().getMaxVelocity();
		float weaponRange = -relativeSpeed * guidedShip.getWeapon().getLifetime();
		return std::max(weaponRange, safeCollisionDistance);
	}

	// todo fix
	//  Vector Field Histogram algorithm
	sf::Vector2f Tactic::avoidCollisions(sf::Vector2f velocity, const Collidables &collidables, const Projectiles &projectiles)
	{
		if (config::debugTactic)
		{
			auto [arrowBase, arrowPoint] = getVectorShapes(velocity, guidedShip.getCenter(), sf::Color::Magenta);

			debugShapes.push_back(std::move(arrowBase));
			debugShapes.push_back(std::move(arrowPoint));
			debugShapes.push_back(makeCircle(guidedShip.getCenter(), safeCollisionDistance + guidedShip.getRadius(), sf::Color::Red));
			////LOG("[%s] Base velocity [%f %f]\n", guidedShip.getId().c_str(), velocity.x, velocity.y);
		}

		auto avoidCollisions = [&]<typename Vec>(const Vec &collidables)
		{
			for (const auto &object : collidables)
			{
				// todo optimize, ugly, why?
				if (object->getId() == guidedShip.getId())
					continue;

				float dist = physics::distance(object->getCollisionCircle(), guidedShip.getCollisionCircle());

				if (dist < safeCollisionDistance)
				{
					sf::Vector2f deltaVector = physics::clampVector(object->getCenter() - guidedShip.getCenter(), 1.0f);
					float angle = physics::getAngleBetweenVectors(velocity, deltaVector);
					////LOG("%s | angle [%f] velocity [%f %f], deltaVector [%f %f]", object->getId().c_str(), angle, velocity.x, velocity.y, deltaVector.x, deltaVector.y);
					// If the obstacle is in front of the ship, adjust the velocity vector
					if (fabs(angle) < 90.f)
					{
						float max = guidedShip.getMaxVelocity() * 2;

						dist = physics::isZero(dist) ? 0.1f : dist;
						float x = safeCollisionDistance / dist;

						float scale = modifiedSigmoid(x, max);
						deltaVector *= scale;
						velocity -= deltaVector;

						if (config::debugTactic)
						{
							auto [arrowBase, arrowPoint] = getVectorShapes(-deltaVector, guidedShip.getCenter(), sf::Color::Red);

							debugShapes.push_back(std::move(arrowBase));
							debugShapes.push_back(std::move(arrowPoint));
						}
						////LOG(" dist [%f], proximity [%f], deltaVectorScaled [%f %f], \n",  dist, modifiedSigmoid(dist, safeCollisionDistance, max),  deltaVector.x, deltaVector.y);
					}
				}
			}
		};

		avoidCollisions(collidables);
		avoidCollisions(projectiles);
		velocity = physics::clampVector(velocity, guidedShip.getMaxVelocity());

		if (config::debugTactic)
		{
			auto [arrowBase, arrowPoint] = getVectorShapes(velocity, guidedShip.getCenter(), sf::Color::Yellow);

			debugShapes.push_back(std::move(arrowBase));
			debugShapes.push_back(std::move(arrowPoint));
		}

		return velocity;
	}
	bool Tactic::noFriendlyFire(const Ships &friends)
	{
		auto &weapon = guidedShip.getWeapon();
		auto projectilePos = weapon.getProjectileSpawnPoint(guidedShip.getRotationCartesian(), guidedShip.getCenter());

		float rectW = guidedShip.getRange();
		float rectH = weapon.getScatter() + 5.f;

		bool noFriendlyFire = true;

		sf::Transform r;
		sf::FloatRect shotPath{{0.f, 0.f}, sf::Vector2f{rectW, rectH}};
		shotPath = r.rotate(guidedShip.getRotationCartesian(), projectilePos).translate(projectilePos - sf::Vector2f{0.f, rectH / 2.f}).transformRect(shotPath);

		for (const auto &ship : friends)
		{
			if (ship->getId() == guidedShip.getId())
				continue;

			// if friendly fire then shouldnt shoot
			noFriendlyFire &= (not shotPath.intersects(ship->getBoundingBox()));
			if (config::debugTactic && (not shotPath.intersects(ship->getBoundingBox())))
			{
				// LOG("[%s] should not shoot - %s in path", guidedShip.getId().c_str(), ship->getId().c_str());
			}
		}

		if (config::debugTactic)
		{
			auto rect = makeRectangle({rectW, rectH}, sf::Color::Magenta);
			rect->setOrigin({0, rectH / 2.f});
			rect->setPosition(projectilePos);
			rect->rotate(guidedShip.getRotationCartesian());
			debugShapes.push_back(rect);
		}
		return noFriendlyFire;
	}

	Tactic::TacticOutcome Tactic::generateTactic(const Ships &friends, const Ships &foes, const Collidables &collidables, const Projectiles &projectiles)
	{
		debugShapes.clear();

		const Ship &target = chooseTarget(foes, friends);
		float ticks = getProjectileInterceptTime(target.getCenter(), target.getVelocity(), target.getRadius());
		float angle = targetAngle(target.getCenter(), target.getVelocity(), target.getRadius(), ticks);

		bool targetInRange = ticks > -0.5f && ticks <= (float)(guidedShip.getWeapon().getLifetime() + tExtra(target.getRadius()));

		bool rotationAchieved = guidedShip.getRotationCartesian() - angle < guidedShip.getWeapon().getScatter();

		sf::Vector2f velocity = encircleTarget(target);
		velocity = avoidCollisions(velocity, collidables, projectiles);

		bool shoot = targetInRange && rotationAchieved && noFriendlyFire(friends);

		if (!shoot)
		{
			auto &weapon = guidedShip.getWeapon();
			float projRange = physics::getVectorMagnitude(target.getVelocity() - guidedShip.getVelocity()) + guidedShip.getRange();
			// LOG("[%s] encricle_dist [%f], dist to target [%f], t [%f], weapon range [%f], velocity [%f %f], inRange %d rotationAchieved %d",
			//	guidedShip.getId().c_str(), calcEncircleDist(target), physics::distance(guidedShip.getCollisionCircle(), target.getCollisionCircle()), ticks,
			//	guidedShip.getRange(), guidedShip.getVelocity().x, guidedShip.getVelocity().y, (int)targetInRange, (int)rotationAchieved);
		}

		return {angle, velocity, shoot, debugShapes};
	}

}