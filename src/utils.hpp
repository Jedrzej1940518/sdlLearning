#pragma once

#include "sdl.hpp"
#include <iostream>
#include <array>
#include <SDL2/SDL_mixer.h>

#define LOG(line) \
    (printf("%s [%d] %s\n", __FILE__, __LINE__, line));

// resolution
extern const uint SCREEN_HEIGHT;
extern const uint SCREEN_WIDTH;
extern const uint FRAME_RATE;

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