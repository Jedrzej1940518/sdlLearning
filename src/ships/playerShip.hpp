#pragma once

#include "ship.hpp"

#include "rendering/collisionObject.hpp"
#include "physics/physics.hpp"
#include "prefabs/prefabs.hpp"

#include <SFML/Window/Event.hpp>

namespace ships
{
    class PlayerShip : public Ship
    {
        bool inputDirections[4];
        void handleInput(physics::DIRECTION dir, bool pressed);

    public:
        PlayerShip(const prefabs::ShipPrefab &prefab, sf::Vector2f position, sf::Vector2f velocity = {0, 0}, float rotation = 0);
        void handleEvents(const sf::Event &event);

        void frameUpdate();
    };
}