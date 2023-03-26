#include "physics.hpp"
#include <algorithm>

namespace physics
{
    double degreesToRadians(double degrees)
    {
        return degrees * M_PI / 180.;
    }
    double radiansToDegrees(double radians)
    {
        return radians / (M_PI / 180.);
    }
    double getVectorRotation(const Vector2d &v)
    {
        // ADD ĆWIARTKI LOL ;D
        cout << radiansToDegrees(atan(v.y / v.x)) << endl;
        return radiansToDegrees(atan(v.y / v.x));
    }
    Vector2d calculateSpeed(const Vector2d &speed, double maxSpeed, double acceleration, double rotation)
    {
        rotation = degreesToRadians(rotation);
        double x1 = 0;
        double y1 = -acceleration;

        Vector2d rotatedVector{cos(rotation) * x1 - sin(rotation) * y1, sin(rotation) * x1 + cos(rotation) * y1};
        Vector2d newSpeed = speed + rotatedVector;

        return clampVector(newSpeed, maxSpeed);
    }
    double vectorLenght(const Vector2d &v)
    {
        return sqrt(v.x * v.x + v.y * v.y);
    }
    Vector2d clampVector(const Vector2d &speed, double maxSpeed)
    {
        double scalingFactor = maxSpeed / vectorLenght(speed);
        if (scalingFactor > 1)
            return speed;
        else
            return speed * scalingFactor;
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

    void printVector(const Vector2d &v)
    {
        printf("[%f,%f]\n", v.x, v.y);
    }

    Vector2d Vector2d::operator+(const Vector2d &rhs) const
    {
        return Vector2d{x + rhs.x, y + rhs.y};
    }
    Vector2d Vector2d::operator-(const Vector2d &rhs) const
    {
        return Vector2d{x - rhs.x, y - rhs.y};
    }
    Vector2d Vector2d::operator*(double factor) const
    {
        return Vector2d{x * factor, y * factor};
    }
    Vector2d Vector2d::operator-() const
    {
        return Vector2d{-x, -y};
    }
} // namespace physics