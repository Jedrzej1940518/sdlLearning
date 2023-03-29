#pragma once

#include "sdl.hpp"
#include <iostream>
#include <array>

#define PRINT(line) \
    (printf("%s [%d] %s\n", __FILE__, __LINE__, line));

extern const uint SCREEN_HEIGHT;
extern const uint SCREEN_WIDTH;

extern const double FRAME_RATE;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;

enum class LevelType
{
    MENU,
    ARENA
};

void printRectangle(SDL_Rect rectangle);
void printPoint(SDL_Point point);
string boolToString(bool b);