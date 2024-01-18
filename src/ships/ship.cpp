#include "ship.hpp"

namespace ships
{

    // todo fix weapon offsets
    Ship::Ship(const prefabs::ShipPrefab &prefab, sf::Vector2f position, sf::Vector2f velocity, float rotation) : CollisionObject{prefab, position, velocity, rotation}, weapon{prefab.weaponPrefab, {0, -spriteRadius - 10}} {}

}