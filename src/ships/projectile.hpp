#pragma once

#include "frameUpdateable.hpp"
#include "killable.hpp"

#include "prefabs/prefabs.hpp"
#include "rendering/collisionObject.hpp"

#include <SFML/Graphics/Drawable.hpp>

namespace ships
{
	class Projectile : public sf::Drawable, public FrameUpdateable, public Killable
	{
		sf::Texture texture;
		sf::Sprite sprite;
		std::string id;
		float spriteRadius;

		sf::Vector2f position;
		sf::Vector2f velocity;
		float rotation;

		int lifetime;
		int dmg;
		int reload;
		float scatterAngle;

	public:
		Projectile(const prefabs::ProjectilePrefab& prefab, sf::Vector2f position, sf::Vector2f velocity = { 0, 0 }, float rotation = 0);

		void frameUpdate() override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void handleCollision(rendering::CollisionObject& oth);

		// setters

		// getters
		physics::Circle getCollisionCircle() const { return physics::Circle{ getCenter(), spriteRadius }; };
		const sf::Vector2f& getCenter() const { return sprite.getPosition(); };
		const sf::Vector2f& getVelocity() const { return velocity; }
		const std::string& getId() const { return id; }
		float getRadius() const { return spriteRadius; }

		virtual ~Projectile();
	};

}