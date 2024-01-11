#include "collisionObject.hpp"
#include "physics/collisionModel.hpp"
#include "object.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <soundManager.hpp>

namespace rendering
{

    CollisionObject::CollisionObject(const prefabs::Prefab &prefab, Vector2d position, Vector2d velocity, double rotation)
        : Object{prefab.texturePath, position, prefab.id}, prefab{prefab}, body{velocity, rotation, prefab.hardware}, collisionParams{false, {0, 0}, 0}, hp{prefab.hp}
    {
        radius = std::max(getWidth(), getHeight()) / 2;
    }
    void CollisionObject::frameUpdate(physics::CollisionModel &collisionModel)
    {
        // debug logs
        //  printCollisionObject();

        body.frameUpdate(collisionParams);
        slowDown(body.getSpeed(), position, collisionModel.getGridParams());

        Object::frameUpdate(body.getSpeed() + body.applyBounce());
        collisionModel.recalculateGridPosition(*this);
    }
    void renderHPBar(SDL_Renderer *renderer, SDL_Rect dest, int currentHP, int maxHP)
    {
        SDL_Rect hpBar{dest};
        hpBar.y -= 20;
        hpBar.h = 10;

        float healthPercentage = static_cast<float>(currentHP) / maxHP;

        int red = static_cast<int>(255 * (1.0 - healthPercentage));
        int green = static_cast<int>(255 * healthPercentage);

        SDL_SetRenderDrawColor(renderer, red, green, 0, 255);

        int hpBarWidth = static_cast<int>(hpBar.w * healthPercentage);

        SDL_Rect hpBarRect = {hpBar.x, hpBar.y, hpBarWidth, hpBar.h};

        SDL_RenderFillRect(renderer, &hpBarRect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &hpBar);
    }

    void CollisionObject::renderObject(SDL_Rect viewport)
    {
        if (not SDL_HasIntersection(&viewport, &dstrect))
            return;
        playSounds();
        SDL_Rect dest = physics::normalizedIntersection(viewport, dstrect);

        // SDL_Intersect wont return -x or -y so we have to acoomodate for that

        if (dest.h < dstrect.h && dest.y <= 0)
        {
            dest.y -= (dstrect.h - dest.h);
        }
        if (dest.w < dstrect.w && dest.x <= 0)
        {
            dest.x -= (dstrect.w - dest.w);
        }
        dest.h = dstrect.h;
        dest.w = dstrect.w;

        if (hp > 0)
        {
            renderHPBar(gRenderer, dest, hp, prefab.hp);
        }

        SDL_RenderCopyEx(gRenderer, texture, NULL, &dest, body.getRotation(), NULL, SDL_FLIP_NONE);
    }

    void CollisionObject::collisionCheck(CollisionObject &oth)
    {
        if (not SDL_HasIntersection(&dstrect, &oth.dstrect) || this == &oth)
            return;

        handleCollision(oth);
    }

    void CollisionObject::handleCollision(CollisionObject &oth)
    {
        if (oth.body.getMass())
        {
            soundsToPlay.insert(Sound::COLLISION);
            constexpr double collisionFactor = 2.0;
            collisionParams = {true, oth.body.getSpeed(), oth.body.getMass()};
            auto sumSpeed = oth.body.getSpeed() - body.getSpeed();
            auto magnitude = physics::vectorLenght(sumSpeed);
            auto dmg = magnitude * oth.body.getMass() / body.getMass() * collisionFactor;
            hit(dmg);
        }
    }

    void CollisionObject::hit(int dmg)
    {
        hp -= dmg;
        alive = hp > 0;
    }

    int CollisionObject::getWidth() const
    {
        return dstrect.w;
    }
    int CollisionObject::getHeight() const
    {
        return dstrect.h;
    }
    int CollisionObject::getRadius() const
    {
        return radius;
    }
    bool CollisionObject::isAlive() const
    {
        return alive;
    }
    const CollisionObject::Body &CollisionObject::getBody() const
    {
        return body;
    }
    physics::Vector2d CollisionObject::getPosition()
    {
        return Object::getPosition();
    }
    physics::Vector2d CollisionObject::getObjectCenter() const
    {
        return Object::getPosition() + physics::Vector2d{getWidth() / 2., getHeight() / 2.};
    }
    double CollisionObject::getRotation()
    {
        return body.getRotation();
    }
    double CollisionObject::getMass() const
    {
        return body.getMass();
    }
    physics::GridPosition &CollisionObject::getGridPosition()
    {
        return gridPosition;
    }
    const physics::GridPosition &CollisionObject::getGridPosition() const
    {
        return gridPosition;
    }
    void CollisionObject::printSpeed() const
    {
        printf("[%s] Velocity {%f, %f}\n", id.c_str(), body.getSpeed().x, body.getSpeed().y);
    }
    void CollisionObject::printGridPosition() const
    {
        auto &g = gridPosition;
        printf("[%s] Grid [%i][%i][%i]\n", id.c_str(), g.row, g.column, g.index);
    }
    void CollisionObject::printCollisionObject() const
    {
        Object::printPosition();
        printSpeed();
        printGridPosition();
        printf("hp %d", hp);
        cout << endl;
    }
} // namespace rendering