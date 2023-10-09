#include "utils.hpp"

const uint SCREEN_HEIGHT = 900;
const uint SCREEN_WIDTH = 1680;
const uint FRAME_RATE = 120;

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
