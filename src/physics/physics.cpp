#include "physics.hpp"
#include <algorithm>

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

Vector2d clampVector(const Vector2d &speed, const Vector2d &maxSpeed)
{
    return {std::clamp(speed.x, -maxSpeed.x, maxSpeed.x), std::clamp(speed.y, -maxSpeed.y, maxSpeed.y)};
}
Vector2d calculatePosition(Vector2d oldPosition, Vector2d offset)
{
    return {oldPosition.x + offset.x, oldPosition.y + offset.y};
}

SDL_Point calculatePosition(SDL_Point oldPosition, Vector2d offset)
{
    return {static_cast<int>(oldPosition.x + offset.x), static_cast<int>(oldPosition.y + offset.y)};
}

void slowDown(Vector2d &speed, Vector2d &position, const GridParams &gridParams)
{
    constexpr auto slowDownDistance = 200;
    if (position.x < slowDownDistance)
        speed.x = 1;
    else if (position.x > gridParams.mapWidth - slowDownDistance)
        speed.x = -1;

    if (position.y < slowDownDistance)
        speed.y = 1;
    else if (position.y > gridParams.mapHeight - slowDownDistance)
        speed.y = -1;
}

void setPosition(SDL_Rect &r, const SDL_Point &p)
{
    r.x = p.x;
    r.y = p.y;
}

void setPosition(SDL_Rect &r, const Vector2d &v)
{
    r.x = static_cast<int>(v.x);
    r.y = static_cast<int>(v.y);
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

void printVector(Vector2d &v)
{
    printf("[%f,%f]\n", v.x, v.y);
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
