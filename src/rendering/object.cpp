#include "object.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

namespace rendering
{

Object::Object(string &&texturePath, Vector2d &&position, string &&id, double parallaxFactor)
    : position{position}, id{id}, parallaxFactor{parallaxFactor}
{
    texture = loadTexture(texturePath);

    SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);

    setPosition(dstrect, position);
}

void Object::frameUpdate(Vector2d offset)
{
    position = calculatePosition(position, offset * parallaxFactor);
    setPosition(dstrect, position);
}

void Object::renderObject(SDL_Rect viewport)
{
    if (not SDL_HasIntersection(&viewport, &dstrect))
        return;

    SDL_Rect src = normalizedIntersection(dstrect, viewport);
    SDL_Rect dest = normalizedIntersection(viewport, dstrect);

    SDL_RenderCopy(gRenderer, texture, &src, &dest);
}

SDL_Rect Object::getDstrect()
{
    return dstrect;
}
int Object::getY()
{
    return dstrect.y;
}
int Object::getX()
{
    return dstrect.x;
}
void Object::printPosition() const
{
    printf("[%s] Position {%u, %u}, W: {%i}, H:{%i}\n", id.c_str(), dstrect.x, dstrect.y, dstrect.w, dstrect.h);
}
} // namespace rendering
