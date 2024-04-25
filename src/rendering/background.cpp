#include "background.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace rendering
{
    Background::Background(const prefabs::Prefab &prefab, sf::Vector2f position, double parallaxFactor) : parallaxFactor{parallaxFactor}, id{prefab.id}
    {
        static int objects{0};
        id = id + "_" + std::to_string(objects);
        ++objects;

        texture.loadFromFile(prefab.texturePath); // TODO optimize to share texture between prefabs probably
        texture.setSmooth(true);
        sprite.setTexture(texture);
        float radius = getSpriteRadius(sprite);
        sprite.setOrigin({ radius, radius });
        sprite.setPosition(position);
    }

    void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
    }

} // namespace rendering
