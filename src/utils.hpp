#pragma once

#include "sdl.hpp"
#include <iostream>

extern const uint WINDOW_HEIGHT;
extern const uint WINDOW_WIDTH;

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