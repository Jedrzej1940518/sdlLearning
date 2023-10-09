#pragma once

#include "sdl.hpp"
#include <iostream>
#include <array>

#define LOG(line) \
    (printf("%s [%d] %s\n", __FILE__, __LINE__, line));

// resolution
inline const uint SCREEN_HEIGHT = 900;
inline const uint SCREEN_WIDTH = 1680;
inline const double FRAME_RATE = 1000 / 10;

// audio
inline int audioFrequency = 44100;
inline int hardwareChannels = 2;
inline int audioChunkSize = 2048;

inline SDL_Window *gWindow = nullptr;
inline SDL_Renderer *gRenderer = nullptr;
inline TTF_Font *gFont = nullptr;

// The music that will be played
inline Mix_Music *gMusic = nullptr;
inline Mix_Chunk *gEngineSound = nullptr;

enum class LevelType
{
    MENU,
    ARENA
};

void printRectangle(SDL_Rect rectangle);
void printPoint(SDL_Point point);
string boolToString(bool b);