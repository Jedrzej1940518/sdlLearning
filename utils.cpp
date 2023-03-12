#include "utils.hpp"

namespace utils
{
    const uint16_t WINDOW_HEIGHT = 400;
    const uint16_t WINDOW_WIDTH = 400;

    const double FRAME_RATE = 1000 / 10;

    SDL_Window *gWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;
    TTF_Font *gFont = nullptr;
}