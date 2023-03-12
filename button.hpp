#pragma once

#include "sdl.hpp"
#include "utils.hpp"
#include <string>

using namespace std;
using namespace utils;

class Button
{
    SDL_Rect position;
    SDL_Color textColor{0, 0, 0};
    SDL_Texture *texture;
    string text;
    int textW;
    int textH;
    bool init{false};

    void initButton();

public:
    void renderButton();
    bool isInside(const SDL_Point &p);
    Button(string text, SDL_Rect position);
};
