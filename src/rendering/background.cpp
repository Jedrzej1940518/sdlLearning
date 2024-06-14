#include "background.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace rendering
{
    Background::Background(const prefabs::Prefab &prefab, sf::Vector2f position, double parallaxFactor) : parallaxFactor{parallaxFactor}, id{prefab.id}
    {
        sprite.setTexture(*(prefab.texture));
        sprite.setScale(1.25f, 1.25f);
        float radius = getSpriteRadius(sprite);
        sprite.setOrigin({radius, radius});
        sprite.setPosition(position);
    }

    void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
    }

} // namespace rendering
