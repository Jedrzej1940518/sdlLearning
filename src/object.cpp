#include "object.hpp"

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

Object::Object(string texturePath, SDL_Point position) : Object(texturePath, position, {0, 0}, Direction::NONE, 0, {0, 0})
{
}
Object::Object(string texturePath, SDL_Point position, Vector2d speed, Direction accelerationDirection, double acceleration, Vector2d maxSpeed) : speed{speed},
                                                                                                                                                  direction{accelerationDirection},
                                                                                                                                                  acceleration{acceleration},
                                                                                                                                                  maxSpeed{maxSpeed}
{
    texture = loadTexture(texturePath);
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    setPosition(dstrect, position);

    dstrect.w = width;
    dstrect.h = height;
}
void Object::frameUpdate(SDL_Rect viewport)
{
    if (isMoving(direction))
    {
        speed = calculateSpeed(speed, maxSpeed, acceleration, direction);
        SDL_Point oldPosition{dstrect.x, dstrect.y};
        SDL_Point newPosition = calculatePosition(speed, oldPosition);
        dstrect.x = newPosition.x;
        dstrect.y = newPosition.y;
        printObject();
    }
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
void Object::accelerate(Direction accelerationDirection)
{
    direction = accelerationDirection;
}

void Object::printObject() const
{
    printf(
        "Position {%i, %i}, Speed {%i, %i}, Acceleration {%f},"\
        "Direction { %s }\n ",
        dstrect.x,
        dstrect.y, speed.x, speed.y, acceleration, directionToString(direction).c_str());
}