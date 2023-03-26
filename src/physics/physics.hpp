#pragma once

#include "../sdl.hpp"
#include "../utils.hpp"
namespace physics
{
    struct Vector2d
    {
        double x;
        double y;
        Vector2d operator+(const Vector2d &rhs) const;
        Vector2d operator-(const Vector2d &rhs) const;
        Vector2d operator*(double factor) const;
        Vector2d operator-() const;
    };

    struct GridCoords
    {
        int row;
        int column;
    };
    struct GridPosition
    {
        int row;
        int column;
        int index;
    };
    struct GridParams
    {
        int mapWidth;
        int mapHeight;
        int cellSide;
    };
    struct CollisionParams
    {
        bool collided;
        Vector2d speed;
        uint mass;
    };
    double getVectorRotation(const Vector2d &v);
    double vectorLenght(const Vector2d &v);
    Vector2d calculateSpeed(const Vector2d &speed, double maxSpeed, double acceleration, double rotation);
    Vector2d clampVector(const Vector2d &speed, double maxSpeed);

    Vector2d calculatePosition(Vector2d oldPosition, Vector2d offset);
    SDL_Point calculatePosition(SDL_Point oldPosition, Vector2d offset);

    void slowDown(Vector2d &speed, Vector2d &position, const GridParams &gridParams);

    SDL_Rect normalizedIntersection(SDL_Rect a, SDL_Rect b);

    void printVector(const Vector2d &v);

    void setPosition(SDL_Rect &r, const SDL_Point &p);
    void setPosition(SDL_Rect &r, const Vector2d &v);

} // namespace physics