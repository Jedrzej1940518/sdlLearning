#pragma once

#include "sdl.hpp"
#include "utils.hpp"
#include <string>

using namespace std;

class Button
{
    SDL_Rect position;
    SDL_Color textColor{0, 0, 0};
    SDL_Texture *texture;
    string text;
    int textW;
    int textH;
public:
    void renderButton();
    bool isInside(const SDL_Point &p);
    Button(string text, SDL_Rect position);
};
