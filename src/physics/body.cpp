
#include "body.hpp"
#include "physics.hpp"

namespace physics
{

Body::Body() : Body{{0, 0}, {0, 0}, {0, 0}, 0, Direction::NONE}
{
}

Body::Body(SDL_Point position, Vector2d speed, Vector2d maxSpeed, double acceleration, Direction accelerationDirection)
    : position{position}, speed{speed}, maxSpeed{maxSpeed}, acceleration{acceleration}, accelerationDirection{
                                                                                            accelerationDirection}
{
}

void Body::frameUpdate()
{
    if (isAccelerating(accelerationDirection))
    {
        speed = calculateSpeed(speed, maxSpeed, acceleration, accelerationDirection);
        accelerationDirection = Direction::NONE;
    }
    if (isMoving(speed))
        position = calculatePosition(position, speed);
}
void Body::accelerate(Direction direction)
{
    accelerationDirection = direction;
}

} // namespace physics