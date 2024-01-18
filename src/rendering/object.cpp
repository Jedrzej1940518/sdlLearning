#include "object.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace rendering
{
    Object::Object(const prefabs::ObjectPrefab &prefab, sf::Vector2f position, sf::Vector2f velocity, float rotation) : body{prefab.maxRotationSpeed, prefab.maxVelocity, prefab.maxAcceleration, prefab.mass}, id{prefab.id}
    {
        static int objects{0};
        id = id + "_" + std::to_string(objects);
        ++objects;

        body.setPosition(position);
        body.setVelocity(velocity);
        body.setRotation(rotation);

        texture.loadFromFile(prefab.texturePath); // TODO optimize
        sprite.setTexture(texture);
        spriteRadius = getSpriteRadius(sprite);

        sprite.setOrigin({spriteRadius, spriteRadius});
        sprite.setPosition(position);
    }

    void Object::frameUpdate()
    {
        body.frameUpdate();
        sprite.setPosition(body.getPosition());
        sprite.setRotation(body.getRotation());
    }
    void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
    }
    // void Object::playSounds()
    // {
    // auto &sm = SoundManager::GetInstance();
    // for (auto sound : soundsToPlay)
    //     sm.playSound(sound);
    // soundsToPlay.clear();
    // }

} // namespace rendering
