#pragma once

#include "mySdl.hpp"
#include "utils.hpp"
#include <string>

namespace rendering
{
    class Text
    {
        string text;
        SDL_Rect position;
        SDL_Color color{0, 0, 0, 0};
        SDL_Texture *texture;
        int textW;
        int textH;

    public:
        Text(string &&text, SDL_Rect &&position, SDL_Color &&color);
        void renderText();
    };
} // namespace rendering