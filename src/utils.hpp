#pragma once

#include "sdl.hpp"
#include <iostream>

using Vector2d = SDL_Point;

extern const uint16_t WINDOW_HEIGHT;
extern const uint16_t WINDOW_WIDTH;

extern const double FRAME_RATE;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;

enum class LevelType
{
    MENU,
    ARENA
};
enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

void printRectangle(SDL_Rect r);
string directionToString(Direction dir);

Vector2d calculateSpeed(Vector2d speed, Vector2d maxSpeed, double acceleration, Direction accelerationDirection);
SDL_Point calculatePosition(Vector2d speed, SDL_Point oldPosition);
void setPosition(SDL_Rect &r, SDL_Point p);
Direction getDirectionFromSdl(SDL_Keycode keyCode);
bool isMoving(Direction direction);