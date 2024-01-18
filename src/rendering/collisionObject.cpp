#include "collisionObject.hpp"
#include "object.hpp"
#include "soundManager.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace rendering
{

    CollisionObject::CollisionObject(const prefabs::CollidablePrefab &prefab, sf::Vector2f position, sf::Vector2f velocity, float rotation)
        : Object{prefab, position, velocity, rotation}, hp{prefab.hp}, maxHp{prefab.hp}
    {
    }

    void CollisionObject::addDebugObjects()
    {
        // obj radius
        shapesToDraw.push_back(std::make_unique<sf::CircleShape>(spriteRadius));
        auto &collisionRadius = *(shapesToDraw.back());
        collisionRadius.setPosition(getCenter() - sf::Vector2f{spriteRadius, spriteRadius});
        collisionRadius.setFillColor(sf::Color::Transparent);
        collisionRadius.setOutlineThickness(3);
        collisionRadius.setOutlineColor(sf::Color::Yellow);
        // obj center
        shapesToDraw.push_back(std::make_unique<sf::CircleShape>(5.f));
        auto &center = *(shapesToDraw.back());
        center.setPosition(getCenter() - sf::Vector2f{5, 5});
        center.setFillColor(sf::Color::Red);
        // maxAcceleration

        // speed
        auto vectorShapes = getVectorShapes(body.getVelocity(), getCenter(), sf::Color::Blue);
        for (auto &vectorShape : vectorShapes)
            shapesToDraw.push_back(std::make_unique<sf::ConvexShape>(vectorShape));
    }

    void CollisionObject::addHpBar()
    {
        constexpr float hpBarH = 10.f;
        constexpr float outlineThickness = 1.f;

        shapesToDraw.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2{spriteRadius * 2, hpBarH}));
        auto &hpBarOutline = shapesToDraw.back();
        hpBarOutline->setPosition(sprite.getPosition());
        hpBarOutline->move({-spriteRadius, spriteRadius + 20.f});
        hpBarOutline->setFillColor(sf::Color::Transparent);
        hpBarOutline->setOutlineColor(sf::Color::Black);
        hpBarOutline->setOutlineThickness(outlineThickness);

        shapesToDraw.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2{spriteRadius * 2, hpBarH}));
        auto &hpBar = shapesToDraw.back();
        hpBar->setPosition(sprite.getPosition());
        hpBar->move({-spriteRadius, spriteRadius + 20.f});

        float healthPercentage = static_cast<float>(hp) / maxHp;

        sf::Uint8 red = static_cast<sf::Uint8>(255 * (1.0 - healthPercentage));
        sf::Uint8 green = static_cast<sf::Uint8>(255 * healthPercentage);
        hpBar->setFillColor(sf::Color{red, green, 0});
        hpBar->setScale(healthPercentage, 1);
    }

    void CollisionObject::frameUpdate()
    {
        shapesToDraw.clear();

        if (collisionParams.collided)
        {
            body.applyCollision(collisionParams);
            collisionParams = {};
        }

        Object::frameUpdate();

        if (debugObject)
            addDebugObjects();

        addHpBar();

        // slowDown(body.getVelocity(), position, collisionModel.getGridParams());
    }

    void CollisionObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        Object::draw(target, states);

        for (auto &shape : shapesToDraw)
            target.draw(*shape, states);
    }

    bool CollisionObject::collisionHappening(const physics::Circle &colliisonCircle)
    {
        return physics::collisionHappening(getCollisionCircle(), colliisonCircle);
    }

    void CollisionObject::handleCollision(const CollisionObject &oth)
    {
        // soundsToPlay.insert(Sound::COLLISION);
        sf::Vector2f collisionVector = oth.getCenter() - getCenter();
        collisionParams = physics::CollisionParams{true, oth.body.getVelocity(), collisionVector, oth.body.getMass()};
        auto sumSpeed = oth.body.getVelocity() - body.getVelocity();
        auto magnitude = physics::vectorLenght(sumSpeed);
        auto dmg = magnitude * oth.body.getMass() / body.getMass() * constants::COLLISION_DAMAGE_FACTOR;
        hit((int)dmg);
    }

    void CollisionObject::hit(int dmg)
    {
        hp -= dmg;
        alive = hp > 0;
    }

} // namespace rendering