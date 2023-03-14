#pragma once

#include "../sdl.hpp"
#include "../utils.hpp"

using Vector2d = SDL_Point;

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

string directionToString(Direction dir);
Direction getDirectionFromSdl(SDL_Keycode keyCode);

bool isAccelerating(Direction accelerationDirection);
bool isMoving(Vector2d speed);

Vector2d calculateSpeed(Vector2d speed, Vector2d maxSpeed, double acceleration, Direction accelerationDirection);
SDL_Point calculatePosition(SDL_Point oldPosition, Vector2d offset);

void setPosition(SDL_Rect &r, SDL_Point p);