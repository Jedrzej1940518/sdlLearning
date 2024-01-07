#pragma once

#include "sdl.hpp"
#include <iostream>
#include <array>
#include <SDL2/SDL_mixer.h>

#define LOG(fmt, ...) \
    (printf("%s [%d] " fmt "\n", __FILE__, __LINE__, __VA_ARGS__));

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