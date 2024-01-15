#include "utils.hpp"
#include <Windows.h>


const unsigned int SCREEN_HEIGHT = 1050;
const unsigned int SCREEN_WIDTH = 1680;
const unsigned int FRAME_RATE = 120;

void printRectangle(SDL_Rect rectangle)
{
    printf("x = %i, y = %i, w = %i, h = %i\n", rectangle.x, rectangle.y, rectangle.w, rectangle.h);
}

void printPoint(SDL_Point point)
{
    printf("x = %i, y = %i\n", point.x, point.y);
}

string getDataPath(string dataPath)
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);

    std::string executablePath(buffer);
    std::string executableDirectory = executablePath.substr(0, executablePath.find_last_of("\\/"));
    return executableDirectory +"\\"+ dataPath;
}

string boolToString(bool b)
{
    return b ? "true" : "false";
}
