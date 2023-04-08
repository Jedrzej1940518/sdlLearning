#include "utils.hpp"

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
