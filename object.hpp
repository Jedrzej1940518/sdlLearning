#pragma once

#include "sdl.hpp"
#include "utils.hpp"

class Object
{
    SDL_Texture *texture;
    SDL_Rect dstrect;

    Vector2d speed;
    Vector2d maxSpeed;
    Direction direction;
    double acceleration;

public:
    Object(string texturePath, SDL_Point position);
    Object(string texturePath, SDL_Point position, Vector2d speed, Direction accelerationDirection, double acceleration, Vector2d maxSpeed);
    
    void accelerate(Direction accelerationDirection);
    void frameUpdate(SDL_Rect viewport);
    
    SDL_Point getPosition() { return {dstrect.x + dstrect.w / 2, dstrect.y + dstrect.h / 2}; }

    void printObject() const;
private:
    void renderObject(SDL_Rect viewport);
};
