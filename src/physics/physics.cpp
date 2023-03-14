#include "physics.hpp"

string directionToString(Direction dir)
{
    switch (dir)
    {
    case Direction::DOWN:
        return "Down";

    case Direction::UP:
        return "Up";

    case Direction::RIGHT:
        return "Right";

    case Direction::LEFT:
        return "Left";

    case Direction::NONE:
        return "None";

    default:
        return "";
    }
}

bool isAccelerating(Direction accelerationDirection)
{
    return accelerationDirection != Direction::NONE;
}

bool isMoving(Vector2d speed)
{
    return speed.x != 0 || speed.y != 0;
}

int addIfNotMax(int a, double b, int max)
{
    return a + b > max ? max : a + b;
}
int addIfNotMin(int a, double b, int min)
{
    return a + b < min ? min : a + b;
}

Vector2d calculateSpeed(Vector2d speed, Vector2d maxSpeed, double acceleration, Direction accelerationDirection)
{
    switch (accelerationDirection)
    {
    case Direction::DOWN:
        speed.y = addIfNotMax(speed.y, acceleration, maxSpeed.y);
        break;
    case Direction::UP:
        speed.y = addIfNotMin(speed.y, -acceleration, -maxSpeed.y);
        break;
    case Direction::RIGHT:
        speed.x = addIfNotMax(speed.x, acceleration, maxSpeed.x);
        break;
    case Direction::LEFT:
        speed.x = addIfNotMin(speed.x, -acceleration, -maxSpeed.x);
        break;
    case Direction::NONE:
        break;
    }
    return speed;
}
SDL_Point calculatePosition(SDL_Point oldPosition, Vector2d offset)
{
    return {oldPosition.x + offset.x, oldPosition.y + offset.y};
}
void setPosition(SDL_Rect &r, SDL_Point p)
{
    r.x = p.x;
    r.y = p.y;
}

Direction getDirectionFromSdl(SDL_Keycode keyCode)
{
    switch (keyCode)
    {
    case SDLK_UP:
        return Direction::UP;
    case SDLK_DOWN:
        return Direction::DOWN;
    case SDLK_LEFT:
        return Direction::LEFT;
    case SDLK_RIGHT:
        return Direction::RIGHT;
    default:
        return Direction::NONE;
    }
}