#include "utils.hpp"

const uint16_t WINDOW_HEIGHT = 1024;
const uint16_t WINDOW_WIDTH = 1024;

const double FRAME_RATE = 1000 / 10;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
TTF_Font *gFont = nullptr;

void printRectangle(SDL_Rect rectangle)
{
    printf("x = %i, y = %i, w = %i, h = %i\n", rectangle.x, rectangle.y, rectangle.w, rectangle.h);
}

void printPoint(SDL_Point point)
{
    printf("x = %i, y = %i\n", point.x, point.y);
}

string boolToString(bool b)
{
    return b ? "true" : "false";
}
