#pragma once

#include "frameUpdateable.hpp"
#include "prefabs/prefabs.hpp"
#include "rendering/collisionObject.hpp"

#include <SFML/Graphics/Drawable.hpp>

namespace ships
{
    class Projectile : public FrameUpdateable, public sf::Drawable
    {
        sf::Texture texture;
        sf::Sprite sprite;
        std::string id;
        float spriteRadius;

        physics::GridPosition gridPosition;

        sf::Vector2f position;
        sf::Vector2f velocity;
        float rotation;

        int lifetime;
        int dmg;
        int reload;
        float scatterAngle;

        bool alive{true};

    public:
        Projectile(const prefabs::ProjectilePrefab &prefab, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, float rotation = 0);

        void frameUpdate() override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        void handleCollision(rendering::CollisionObject &oth);

        // setters
        void setGridPosition(physics::GridPosition gp) { gridPosition = gp; };
        // getters
        physics::Circle getCollisionCircle() const { return physics::Circle{getCenter(), spriteRadius}; };
        const physics::GridPosition &getGridPosition() const { return gridPosition; }
        const sf::Vector2f &getCenter() const { return sprite.getPosition(); };
        bool isAlive() { return alive; }

        virtual ~Projectile();
    };

}