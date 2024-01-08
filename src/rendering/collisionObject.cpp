#include "collisionObject.hpp"
#include "../physics/collisionModel.hpp"
#include "object.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
namespace rendering
{

    CollisionObject::CollisionObject(const prefabs::Prefab &prefab, Vector2d position, Vector2d speed, double rotation)
        : Object{prefab.texturePath, position, prefab.id}, prefab{prefab}, body{speed, rotation, prefab.hardware}, collisionParams{false, {0, 0}, 0}, hp{prefab.hp}
    {
    }
    void CollisionObject::frameUpdate(physics::CollisionModel &collisionModel)
    {
        // debug logs
        // printCollisionObject();

        body.frameUpdate(collisionParams);
        slowDown(body.getSpeed(), position, collisionModel.getGridParams());

        Object::frameUpdate(body.getSpeed() + body.applyBounce());
        collisionModel.recalculateGridPosition(*this);
    }

    void CollisionObject::renderObject(SDL_Rect viewport)
    {
        if (not SDL_HasIntersection(&viewport, &dstrect))
            return;

        SDL_Rect src = physics::normalizedIntersection(dstrect, viewport);
        SDL_Rect dest = physics::normalizedIntersection(viewport, dstrect);

        SDL_RenderCopyEx(gRenderer, texture, &src, &dest, body.getRotation(), NULL, SDL_FLIP_NONE);
    }

    void CollisionObject::collisionCheck(CollisionObject &oth)
    {
        printf("collision check between %s and %s\n", id.c_str(), oth.id.c_str());
        if (not SDL_HasIntersection(&dstrect, &oth.dstrect) || this == &oth)
            return;

        handleCollision(oth);
    }

    void CollisionObject::handleCollision(CollisionObject &oth)
    {
        if (oth.body.getMass())
            collisionParams = {true, oth.body.getSpeed(), oth.body.getMass()};
    }

    void CollisionObject::hit(int dmg)
    {
        hp -= dmg;
        if (hp <= 0)
            alive = false;
    }

    int CollisionObject::getWidth() const
    {
        return dstrect.w;
    }
    int CollisionObject::getHeight() const
    {
        return dstrect.h;
    }
    bool CollisionObject::isAlive() const
    {
        return alive;
    }
    CollisionObject::Body &CollisionObject::getBody()
    {
        return body;
    }
    physics::Vector2d CollisionObject::getPosition()
    {
        return Object::getPosition();
    }
    double CollisionObject::getRotation()
    {
        return body.getRotation();
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
        printf("[%s] Speed {%f, %f}\n", id.c_str(), body.getSpeed().x, body.getSpeed().y);
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