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
  class Object : public FrameUpdateable, public sf::Drawable
  {

  protected:
    std::string id;

    sf::Texture texture;
    sf::Sprite sprite;
    float spriteRadius;

    physics::Body body;

    // std::unordered_set<Sound> soundsToPlay;

  public:
    Object(const prefabs::ObjectPrefab &prefab, sf::Vector2f position = {0, 0}, sf::Vector2f velocity = {0, 0}, float rotation = 0);

    void frameUpdate() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    // void playSounds();

    // getters
    const sf::Sprite &getSprite() const { return sprite; };
    const std::string &getId() const { return id; }
    const sf::Vector2f &getVelocity() const { return body.getVelocity(); }

    // our sprites are by default facing NORTH which is -90. So object with rotation 0 is facing -90 in cartesian coordinates.
    float getRotationCartesian() const { return physics::normalizeDegrees(body.getRotation() - 90); }
    virtual ~Object() {}
  };
} // namespace rendering
