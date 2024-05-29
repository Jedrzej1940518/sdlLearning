#pragma once

#include "utils.hpp"
#include "prefabs/prefabs.hpp"

// #include "soundManager.hpp"

#include <unordered_set>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace rendering
{
    class Background : public sf::Drawable
    {

    protected:
        sf::Sprite sprite;
        std::string id{"Background"};

        double parallaxFactor;
        // std::unordered_set<Sound> soundsToPlay;

    public:
        Background(const prefabs::Prefab &prefab, sf::Vector2f position = {0, 0}, double parallaxFactor = 1.0);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        const sf::Sprite &getSprite() const { return sprite; };
        const std::string &getId() const { return id; }

        virtual ~Background() {}
    };
} // namespace rendering
