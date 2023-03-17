#pragma once

#include "../sdl.hpp"
#include "../utils.hpp"

struct Vector2d
{
    double x;
    double y;
    Vector2d operator+(const Vector2d &rhs);
    Vector2d operator-(const Vector2d &rhs);
    Vector2d operator*(double factor);
    Vector2d operator-();
};

struct GridPosition
{
    int row;
    int column;
    int index;
};

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

constexpr int directionNumber = static_cast<int>(Direction::NONE);

string directionToString(Direction dir);
Direction getDirectionFromSdl(SDL_Keycode keyCode);

bool isAccelerating(Direction accelerationDirection);
bool isMoving(Vector2d speed);

Vector2d calculateSpeed(Vector2d speed, Vector2d maxSpeed, double acceleration, Direction accelerationDirection);
Vector2d calculatePosition(Vector2d oldPosition, Vector2d offset);
SDL_Point calculatePosition(SDL_Point oldPosition, Vector2d offset);

SDL_Point vectorToPoint(Vector2d vector2d);

SDL_Rect normalizedIntersection(SDL_Rect a, SDL_Rect b);

void setPosition(SDL_Rect &r, SDL_Point p);