#include "collisionObject.hpp"
#include "../physics/collisionModel.hpp"
#include "object.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
namespace rendering
{

CollisionObject::CollisionObject(string &&texturePath, string &&id, Vector2d &&position, Body &&body,
                                 CollisionModel &collisionModel)
    : Object{std::move(texturePath), std::move(position), std::move(id)}, body{body}, collisionModel{collisionModel},
      collisionParams{false, {0, 0}}
{
    collisionModel.emplace(this);
}
void CollisionObject::frameUpdate()
{
    body.frameUpdate(collisionParams);
    slowDown(body.getSpeed(), position, collisionModel.getGridParams());
    Object::frameUpdate(body.getSpeed());
    collisionModel.recalculateGridPosition(*this);
}

void CollisionObject::collisionCheck(CollisionObject &oth)
{
    if (not SDL_HasIntersection(&dstrect, &oth.dstrect) || this == &oth)
        return;

    this->collisionParams = {true, oth.body.getSpeed()};
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
void CollisionObject::printSpeed()
{
    printf("[%s] Speed {%f, %f}\n", id.c_str(), body.getSpeed().x, body.getSpeed().y);
}
void CollisionObject::printGridPosition() const
{
    auto &g = gridPosition;
    printf("[%s] Grid [%i][%i][%i]\n", id.c_str(), g.row, g.column, g.index);
}
} // namespace rendering