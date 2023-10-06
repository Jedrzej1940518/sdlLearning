#pragma once

#include "../sdl.hpp"
#include <boost/circular_buffer.hpp>
#include "line.hpp"
#include <string>

namespace interpreter
{
    class Lines
    {
        constexpr static uint maxLines{8};

        SDL_Rect dstrect;
        SDL_Renderer *renderer;

        TTF_Font *font;
        boost::circular_buffer<Line> lines;

        void initTextSize();

        int textH;

        string start{"Jedrzej$ "};

    public:
        Lines(SDL_Rect &&dstrect, SDL_Renderer *renderer) : dstrect{dstrect}, renderer{renderer}, lines{maxLines}
        {
            newLine();
            initTextSize();
        }
        void newLine();
        void push_back(char c);
        void pop_back();
        void render();
        auto back() { return lines.back(); }
    };
}