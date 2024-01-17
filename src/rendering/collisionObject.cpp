#include "collisionObject.hpp"
#include "object.hpp"
#include "soundManager.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace rendering
{

    CollisionObject::CollisionObject(const prefabs::Prefab &prefab, sf::Vector2f position, sf::Vector2f velocity, float rotation)
        : prefab{prefab}, Object{prefab, position}
    {
        body.setVelocity(velocity);
        body.setRotation(rotation);
        auto rect = sprite.getTextureRect();
        float radius = std::max(rect.width / 2.f, rect.height / 2.f);
        collisionCircle = {sprite.getPosition() + sf::Vector2f{radius, radius}, radius};
    }
    void CollisionObject::frameUpdate(/*physics::CollisionModel &collisionModel*/)
    {
        if (debugObject && collisionParams.collided)
        {
            cpCopy = collisionParams;
            cpCopy.collisionVector *= 0.05f;
        }

        body.consumeCollision(collisionParams);
        sprite.move(body.consumeBounce());
        Object::frameUpdate();
        collisionCircle.position = sprite.getPosition() + sf::Vector2f{collisionCircle.radius, collisionCircle.radius};

        if (debugObject)
        {
            // colision radius
            debugShapes.clear();
            debugShapes.push_back(std::make_unique<sf::CircleShape>(collisionCircle.radius));
            auto &collisionRadius = *(debugShapes.back());
            collisionRadius.setPosition(getCenter() - sf::Vector2f{collisionCircle.radius, collisionCircle.radius});
            collisionRadius.setFillColor(sf::Color::Transparent);
            collisionRadius.setOutlineThickness(3);
            collisionRadius.setOutlineColor(sf::Color::Yellow);
            // obj center
            debugShapes.push_back(std::make_unique<sf::CircleShape>((float)5));
            auto &center = *(debugShapes.back());
            center.setPosition(getCenter() - sf::Vector2f{5, 5});
            center.setFillColor(sf::Color::Red);
            // acceleration

            // speed
            auto vectorShapes = getVectorShapes(body.getVelocity(), getCenter(), sf::Color::Blue);
            for (auto &vectorShape : vectorShapes)
                debugShapes.push_back(std::make_unique<sf::ConvexShape>(vectorShape));
            // collision
            vectorShapes = getVectorShapes(cpCopy.collisionVector, getCenter(), sf::Color::Green);
            for (auto &vectorShape : vectorShapes)
                debugShapes.push_back(std::make_unique<sf::ConvexShape>(vectorShape));

            // debugShapes.push_back(std::make_unique<sf::ConvexShape>(getVectorShape(cpCopy.collisionVector)));
            // debugShapes.back()->setFillColor(sf::Color::Green);
            // debugShapes.back()->setPosition(getCenter());
        }
        // body.frameUpdate(collisionParams);
        // debug logs
        //  printCollisionObject();

        // body.frameUpdate(collisionParams);
        // slowDown(body.getVelocity(), position, collisionModel.getGridParams());

        // Object::frameUpdate(body.getVelocity() + body.consumeBounce());
        // collisionModel.recalculateGridPosition(*this);
    }

    void CollisionObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        Object::draw(target, states);

        for (auto &shape : debugShapes)
            target.draw(*shape, states);
    }
    // void renderHPBar(SDL_Renderer *renderer, SDL_Rect dest, int currentHP, int maxHP)
    // {
    //     SDL_Rect hpBar{dest};
    //     hpBar.y -= 20;
    //     hpBar.h = 10;

    //     float healthPercentage = static_cast<float>(currentHP) / maxHP;

    //     int red = static_cast<int>(255 * (1.0 - healthPercentage));
    //     int green = static_cast<int>(255 * healthPercentage);

    //     SDL_SetRenderDrawColor(renderer, red, green, 0, 255);

    //     int hpBarWidth = static_cast<int>(hpBar.w * healthPercentage);

    //     SDL_Rect hpBarRect = {hpBar.x, hpBar.y, hpBarWidth, hpBar.h};

    //     SDL_RenderFillRect(renderer, &hpBarRect);

    //     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //     SDL_RenderDrawRect(renderer, &hpBar);
    // }

    // void CollisionObject::debugRender(SDL_Rect viewport)
    // {
    // auto pos = getObjectCenter() - physics::sf::Vector2f{(double)viewport.x, (double)viewport.y};
    // auto color = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 0, 0, 255);
    // lineColor(gRenderer, pos.x, pos.y, pos.x + body.getVelocity().x * 50, pos.y + body.getVelocity().y * 50, color);

    // auto accelerationVector = physics::getRotatedVector(getBody().getAccelerationAngle() - 180);
    // color = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 0, 255, 255);
    // lineColor(gRenderer, pos.x, pos.y, pos.x + accelerationVector.x * 50, pos.y + accelerationVector.y * 50, color);

    // color = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32), 255, 255, 0);
    // ellipseColor(gRenderer, pos.x, pos.y, radius, radius, color);
    // }

    // void CollisionObject::renderObject(SDL_Rect viewport)
    // {
    //     if (not SDL_HasIntersection(&viewport, &dstrect))
    //         return;
    //     playSounds();
    //     SDL_Rect dest = physics::normalizedIntersection(viewport, dstrect);

    //     // SDL_Intersect wont return -x or -y so we have to acoomodate for that

    //     if (dest.h < dstrect.h && dest.y <= 0)
    //     {
    //         dest.y -= (dstrect.h - dest.h);
    //     }
    //     if (dest.w < dstrect.w && dest.x <= 0)
    //     {
    //         dest.x -= (dstrect.w - dest.w);
    //     }
    //     dest.h = dstrect.h;
    //     dest.w = dstrect.w;

    //     if (hp > 0)
    //     {
    //         renderHPBar(gRenderer, dest, hp, prefab.hp);
    //     }

    //     SDL_RenderCopyEx(gRenderer, texture, NULL, &dest, body.getRotation(), NULL, SDL_FLIP_NONE);

    //     if (debugObject)
    //         debugRender(viewport);
    // }

    const physics::Circle &CollisionObject::getCollisionCircle() const
    {
        return collisionCircle;
    }
    void CollisionObject::collisionCheck(const CollisionObject &oth)
    {
        if ((&oth == this) || not physics::collisionHappening(getCollisionCircle(), oth.getCollisionCircle()))
            return;

        handleCollision(oth);
    }

    void CollisionObject::handleCollision(const CollisionObject &oth)
    {
        if (oth.body.getMass())
        {
            // soundsToPlay.insert(Sound::COLLISION);
            sf::Vector2f collisionVector = oth.getCenter() - getCenter();
            collisionParams = physics::CollisionParams{true, oth.body.getVelocity(), collisionVector, oth.body.getMass()};
            auto sumSpeed = oth.body.getVelocity() - body.getVelocity();
            auto magnitude = physics::vectorLenght(sumSpeed);
            auto dmg = magnitude * oth.body.getMass() / body.getMass() * constants::collisionDamageFactor;
            // hit((int)dmg);
        }
    }

    // void CollisionObject::hit(int dmg)
    // {
    //     hp -= dmg;
    //     alive = hp > 0;
    // }

    // int CollisionObject::getWidth() const
    // {
    //     return dstrect.w;
    // }
    // int CollisionObject::getHeight() const
    // {
    //     return dstrect.h;
    // }
    // int CollisionObject::getRadius() const
    // {
    //     return radius;
    // }
    // bool CollisionObject::isAlive() const
    // {
    //     return alive;
    // }
    // const CollisionObject::Body &CollisionObject::getBody() const
    // {
    //     return body;
    // }
    // physics::sf::Vector2f CollisionObject::getPosition()
    // {
    //     return Object::getPosition();
    // }
    // physics::sf::Vector2f CollisionObject::getObjectCenter() const
    // {
    //     return Object::getPosition() + physics::sf::Vector2f{getWidth() / 2., getHeight() / 2.};
    // }
    // double CollisionObject::getRotation()
    // {
    //     return body.getRotation();
    // }
    // double CollisionObject::getMass() const
    // {
    //     return body.getMass();
    // }
    // physics::GridPosition &CollisionObject::getGridPosition()
    // {
    //     return gridPosition;
    // }
    const sf::Vector2f &CollisionObject::getCenter() const
    {
        return collisionCircle.position;
    }
    void CollisionObject::setGridPosition(physics::GridPosition gP)
    {
        gridPosition = gP;
    }
    const physics::GridPosition &CollisionObject::getGridPosition() const
    {
        return gridPosition;
    }
    // void CollisionObject::printSpeed() const
    // {
    //     printf("[%s] Velocity {%f, %f}\n", id.c_str(), body.getVelocity().x, body.getVelocity().y);
    // }
    void CollisionObject::printGridPosition() const
    {
        auto &g = gridPosition;
        printf("[%s] Grid [%i][%i][%i]\n", id.c_str(), g.row, g.column, g.index);
    }
    // void CollisionObject::printCollisionObject() const
    // {
    //     Object::printPosition();
    //     printSpeed();
    //     printGridPosition();
    //     printf("hp %d", hp);
    //     cout << endl;
    // }
} // namespace rendering