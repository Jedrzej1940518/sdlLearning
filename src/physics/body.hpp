#pragma once

#include "physics.hpp"
#include <SDL2/SDL_rect.h>

namespace physics
{

class Body
{

    SDL_Point position;

    Vector2d speed;
    Vector2d maxSpeed;
    double acceleration;
    Direction accelerationDirection;

  public:
    Body();
    Body(SDL_Point position, Vector2d speed, Vector2d maxSpeed, double acceleration, Direction accelerationDirection);

    void accelerate(Direction direction);
    void frameUpdate();

    SDL_Point getPosition() const
    {
        return position;
    }
    void printBody() const
    {
        printf("Position {%i, %i}, Speed {%i, %i}, Direction {%s}\n", position.x, position.y, speed.x, speed.y,
               directionToString(accelerationDirection).c_str());
    }
};
} // namespace physics