#include "object.hpp"
#include <SDL2/SDL_rect.h>

SDL_Rect normalizedIntersection(SDL_Rect a, SDL_Rect b)
{
    int x = a.x;
    int y = a.y;

    a.x = 0;
    a.y = 0;
    b.x -= x;
    b.y -= y;

    SDL_Rect res;
    SDL_IntersectRect(&a, &b, &res);
    return res;
}

Object::Object(string texturePath, SDL_Point position)
    : Object(texturePath, Body{position, {0, 0}, {0, 0}, 0, Direction::NONE})
{
}
Object::Object(string texturePath, Body body) : body{body}
{
    texture = loadTexture(texturePath);
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    setPosition(dstrect, body.getPosition());

    dstrect.w = width;
    dstrect.h = height;
}
void Object::frameUpdate(SDL_Rect viewport)
{
    body.frameUpdate();
    setPosition(dstrect, body.getPosition());
    renderObject(viewport);
}
void Object::renderObject(SDL_Rect viewport)
{
    if (not SDL_HasIntersection(&viewport, &dstrect))
        return;

    SDL_Rect src = normalizedIntersection(dstrect, viewport);
    SDL_Rect dest = normalizedIntersection(viewport, dstrect);

    SDL_RenderCopy(gRenderer, texture, &src, &dest);
}