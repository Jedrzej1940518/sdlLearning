#pragma once

#include "utils.hpp"
#include "object.hpp"
#include "physics/body.hpp"
#include "physics/physics.hpp"
#include "prefabs/prefabs.hpp"

#include <memory>

#include <SFML/Graphics/Shape.hpp>

namespace rendering
{
	class CollisionObject : public Object, public Killable
	{
	protected:
		std::vector<std::shared_ptr<sf::Shape>> shapesToDraw;
		physics::CollisionParams collisionParams;

		const int maxHp;
		int hp;

		void addDebugObjects();
		void addHpBar();

	public:
		CollisionObject(const prefabs::CollidablePrefab& prefab, sf::Vector2f position, sf::Vector2f velocity = { 0, 0 }, float rotation = 0);

		void handleCollision(const CollisionObject& oth);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void frameUpdate() override;
		void hit(int dmg);

		// setters

		// getters
		const physics::Circle getCollisionCircle() const { return physics::Circle{ getCenter(), spriteRadius }; };
		const sf::Vector2f& getCenter() const { return body.getPosition(); };
		const sf::FloatRect getBoundingBox() const { return sprite.getGlobalBounds(); }

		float getMass() const { return body.getMass(); };

		virtual ~CollisionObject() {}
	};
} // namespace rendering