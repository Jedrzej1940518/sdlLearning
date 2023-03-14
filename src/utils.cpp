#include "utils.hpp"

const uint16_t WINDOW_HEIGHT = 1024;
const uint16_t WINDOW_WIDTH = 1024;

const double FRAME_RATE = 1000 / 10;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
TTF_Font *gFont = nullptr;

void printRectangle(SDL_Rect r)
{
    printf("x = %u, y = %u, w = %u, h = %u\n", r.x, r.y, r.w, r.h);
}
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

bool isMoving(Direction direction) { return direction != Direction::NONE; }

//TODO vector2d speed -> double
//TODO multiple acceleration directions?

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
SDL_Point calculatePosition(Vector2d speed, SDL_Point oldPosition)
{
    return {oldPosition.x + speed.x, oldPosition.y + speed.y};
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