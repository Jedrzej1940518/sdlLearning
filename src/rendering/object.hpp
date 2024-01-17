#pragma once

#include "utils.hpp"
#include "prefabs/prefabs.hpp"
#include "physics/body.hpp"
// #include "soundManager.hpp"

#include <unordered_set>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace rendering
{
  class Object : public sf::Drawable
  {

  protected:
    sf::Texture texture;
    sf::Sprite sprite;
    physics::Body body;

    std::string id;
    double parallaxFactor;
    // std::unordered_set<Sound> soundsToPlay;

  public:
    Object(const prefabs::Prefab &prefab, sf::Vector2f absolutePosition = {0, 0}, double parallaxFactor = 1.0);

    const sf::Sprite &getSprite() const;

    void printPosition() const;

    virtual void frameUpdate();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void playSounds();
    sf::Vector2f getVelocity() const { return body.getVelocity(); }
    // virtual void renderObject();

    const std::string &getId() const { return id; }

    virtual ~Object()
    {
    }
  };
} // namespace rendering
