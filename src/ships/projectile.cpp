#include "projectile.hpp"
// #include "soundManager.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace ships
{

	void Projectile::handleCollision(rendering::CollisionObject& oth)
	{
		// auto sound = projectilePrefab.dmg > 6 ? Sound::SHELL_HIT_BIG : Sound::SHELL_HIT_SMALL;
		// soundsToPlay.insert(sound);
		// playSounds();
		oth.hit(dmg);
		alive = false;
	}
	void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}
	Projectile::Projectile(const prefabs::ProjectilePrefab& prefab, sf::Vector2f position, sf::Vector2f velocity, float rotation) : position{ position }, velocity{ velocity }, rotation{ rotation }, lifetime{ prefab.lifetime }, dmg{ prefab.dmg }, reload{ prefab.reload }, scatterAngle{ prefab.scatterAngle }
	{
		static int projectiles{ 0 };
		id = prefab.id + "_" + std::to_string(projectiles);
		++projectiles;

		texture.loadFromFile(prefab.texturePath); // TODO optimize
		texture.setSmooth(true);
		sprite.setTexture(texture);
		spriteRadius = getSpriteRadius(sprite);
		sprite.setOrigin({ spriteRadius, spriteRadius });
		sprite.setPosition(position);
		sprite.rotate(rotation);
	}

	Projectile::~Projectile()
	{
	}

	void Projectile::frameUpdate()
	{
		sprite.move(velocity);
		--lifetime;
		alive &= lifetime > 0;
	};
}
