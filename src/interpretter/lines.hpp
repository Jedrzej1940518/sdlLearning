#pragma once

#include "../sdl.hpp"
#include <boost/circular_buffer.hpp>
#include "line.hpp"
#include <string>

namespace interpretter
{
    class Lines
    {
        SDL_Texture *texture;
        SDL_Renderer *renderer;
        TTF_Font *font;
        SDL_Rect dstrect;
        boost::circular_buffer<Line> lines{maxLines};

        Lines(SDL_Rect &&dstrect, SDL_Renderer *renderer) : dstrect{dstrect}, renderer{renderer} { initTextSize(); }

        constexpr uint maxLines{8};
        int textH;

        string start{"Jedrzej$ "};

    public:
        void newLine();
        void push_back(char c);
        void pop();
        void render();
    };
}