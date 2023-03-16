#include "collisionObject.hpp"
#include "object.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
namespace rendering
{

CollisionObject::CollisionObject(string texturePath, Body body)
    : Object{texturePath, vectorToPoint(body.getPosition())}, body{body}
{
}
void CollisionObject::frameUpdate()
{
    body.frameUpdate(collison.collided);
    Object::frameUpdate(body.getSpeed());
}
bool CollisionObject::collides(const CollisionObject &other)
{
    if (not SDL_HasIntersection(&dstrect, &other.dstrect))
        return false;

    collison.speedSum = body.getSpeed() - other.body.getSpeed();
    collison.collided = true;
    return true;
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
} // namespace rendering