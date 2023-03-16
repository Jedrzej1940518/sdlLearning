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

double addIfNotMax(double a, double b, double max)
{
    return a + b > max ? max : a + b;
}
double addIfNotMin(double a, double b, double min)
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
Vector2d calculatePosition(Vector2d oldPosition, Vector2d offset)
{
    return {oldPosition.x + offset.x, oldPosition.y + offset.y};
}

SDL_Point calculatePosition(SDL_Point oldPosition, Vector2d offset)
{
    return {static_cast<int>(oldPosition.x + offset.x), static_cast<int>(oldPosition.y + offset.y)};
}

SDL_Point vectorToPoint(Vector2d vector2d)
{
    return {static_cast<int>(vector2d.x), static_cast<int>(vector2d.y)};
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

Vector2d Vector2d::operator+(const Vector2d &rhs)
{
    return Vector2d{x + rhs.x, y + rhs.y};
}
Vector2d Vector2d::operator-(const Vector2d &rhs)
{
    return Vector2d{x - rhs.x, y - rhs.y};
}
Vector2d Vector2d::operator*(double factor)
{
    return Vector2d{x * factor, y * factor};
}
Vector2d Vector2d::operator-()
{
    return Vector2d{-x, -y};
}
