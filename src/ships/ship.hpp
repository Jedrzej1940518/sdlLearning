#pragma once

#include "rendering/collisionObject.hpp"
#include "physics/physics.hpp"
// #include "physics/collisionModel.hpp"
#include "prefabs/prefabs.hpp"
// #include "projectile.hpp"

#include <SFML/Window/Event.hpp>

namespace ships
{
    class Ship : public rendering::CollisionObject
    {
        bool inputDirections[4];
        bool spawnProjectile;
        int shellReload{0};

        void handleInput(physics::DIRECTION dir, bool pressed);

    public:
        Ship(const prefabs::Prefab &prefab, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, float rotation = 0);

        void shoot();
        void handleEvents(const sf::Event &event);

        // void rotateLeft();
        // void rotateRight();
        // void stopRotateLeft();
        // void stopRotateRight();

        void frameUpdate();

        // void renderReload(SDL_Rect viewport);
        // void renderObject(SDL_Rect viewport) override;
        // Projectile *frameUpdate(CollisionModel &collisionModel);
    };
}