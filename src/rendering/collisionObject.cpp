#include "collisionObject.hpp"
#include "object.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
namespace rendering
{

CollisionObject::CollisionObject(string &&texturePath, string &&id, Vector2d &&position, Body &&body)
    : Object{std::move(texturePath), std::move(position), std::move(id)}, body{body}, collisionParams{false, {0, 0}}
{
}
void CollisionObject::frameUpdate()
{
    body.frameUpdate(collisionParams);
    Object::frameUpdate(body.getSpeed());
}

void CollisionObject::collisionCheck(CollisionObject &a, CollisionObject &b)
{
    if (not SDL_HasIntersection(&a.dstrect, &b.dstrect) || &a == &b)
        return;

    a.collisionParams = {true, b.body.getSpeed()};
    b.collisionParams = {true, a.body.getSpeed()};
}

int CollisionObject::getWidth() const
{
    return dstrect.w;
}
int CollisionObject::getHeight() const
{
    return dstrect.h;
}
CollisionObject::Body &CollisionObject::getBody()
{
    return body;
}
GridPosition &CollisionObject::getGridPosition()
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
} // namespace rendering