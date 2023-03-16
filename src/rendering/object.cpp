#include "object.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

namespace rendering
{

Object::Object(string texturePath, SDL_Point position, double parallaxFactor) : parallaxFactor{parallaxFactor}
{
    texture = loadTexture(texturePath);

    int width = 0;
    int height = 0;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    dstrect = {position.x, position.y, width, height};
}

void Object::frameUpdate(Vector2d offset)
{
    SDL_Point position{dstrect.x, dstrect.y};
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
    printf("Position {%u, %u}\n", dstrect.x, dstrect.y);
}
} // namespace rendering
