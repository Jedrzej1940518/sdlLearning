#pragma once

#include "sdl.hpp"
#include <iostream>

namespace utils
{

    extern const uint16_t WINDOW_HEIGHT;
    extern const uint16_t WINDOW_WIDTH;

    extern const double FRAME_RATE;

    extern SDL_Window *gWindow;
    extern SDL_Renderer *gRenderer;
    extern TTF_Font* gFont;

    enum class Level
    {
        MENU,
        ARENA
    };
}