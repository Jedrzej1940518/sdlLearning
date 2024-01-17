#include "object.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace rendering
{
    Object::Object(const prefabs::Prefab &prefab, sf::Vector2f absolutePosition, double parallaxFactor) : parallaxFactor{parallaxFactor}, body{prefab.maxRotationSpeed, prefab.maxVelocity, prefab.acceleration, prefab.mass}, id{prefab.id}
    {
        static int objects{0};
        id = id + "_" + std::to_string(objects);
        ++objects;

        texture.loadFromFile(prefab.texturePath); // TODO optimize
        sprite.setTexture(texture);
        sprite.setPosition(absolutePosition);
    }

    const sf::Sprite &Object::getSprite() const
    {
        return sprite;
    }

    // Object::Object(const string &texturePath, sf::Vector2<int> &position, const string &id, double parallaxFactor)
    //     : position{position}, id{id}, parallaxFactor{parallaxFactor}
    // {
    // }

    void Object::frameUpdate()
    {
        body.frameUpdate();
        sprite.move(body.getVelocity());
        // position = calculatePosition(position, offset * parallaxFactor);
        // setPosition(dstrect, position);
    }
    void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
    }
    void Object::playSounds()
    {
        // auto &sm = SoundManager::GetInstance();
        // for (auto sound : soundsToPlay)
        //     sm.playSound(sound);
        // soundsToPlay.clear();
    }
    // void Object::renderObject()
    // {
    //     // if (not SDL_HasIntersection(&viewport, &dstrect))
    //     //     return;
    //     // playSounds();
    //     // SDL_Rect src = physics::normalizedIntersection(dstrect, viewport);
    //     // SDL_Rect dest = physics::normalizedIntersection(viewport, dstrect);

    //     // SDL_RenderCopy(gRenderer, texture, &src, &dest);
    //     window.draw(sprite);
    // }

    void Object::printPosition() const
    {
        // printf("[%s] Position {%u, %u}, W: {%i}, H:{%i}\n", id.c_str(), dstrect.x, dstrect.y, dstrect.w, dstrect.h);
    }
} // namespace rendering
