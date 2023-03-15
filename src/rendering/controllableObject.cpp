#include "controllableObject.hpp"
#include "object.hpp"
#include <SDL2/SDL_rect.h>
namespace rendering
{

ControllableObject::ControllableObject(string texturePath, SDL_Rect dstrect, Body body)
    : Object{texturePath, dstrect}, body{body}
{
}
void ControllableObject::frameUpdate()
{
    body.frameUpdate();
    Object::frameUpdate(body.getSpeed());
}

int ControllableObject::getWidth() const
{
    return dstrect.w;
}
int ControllableObject::getHeight() const
{
    return dstrect.h;
}
ControllableObject::Body &ControllableObject::getBody()
{
    return body;
}
} // namespace rendering