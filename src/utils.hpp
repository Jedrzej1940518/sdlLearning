#pragma once

#include "sdl.hpp"
#include <iostream>
#include <array>

#define LOG(line) \
    (printf("%s [%d] %s\n", __FILE__, __LINE__, line));

inline const uint SCREEN_HEIGHT = 900;
inline const uint SCREEN_WIDTH = 1680;
inline const double FRAME_RATE = 1000 / 10;

inline SDL_Window *gWindow = nullptr;
inline SDL_Renderer *gRenderer = nullptr;
inline TTF_Font *gFont = nullptr;

enum class LevelType
{
    MENU,
    ARENA
};

void printRectangle(SDL_Rect rectangle);
void printPoint(SDL_Point point);
string boolToString(bool b);