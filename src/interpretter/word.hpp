#pragma once

#include <string>

#include "instructions.hpp"
#include "../sdl.hpp"

namespace interpretter
{
    enum class Colors
    {
        DEFAULT = SDL_Color{255, 255, 255, 255},   // white
        INSTRUCTION = SDL_Color{0, 255, 0, 255},   // green
        START_OF_LINE = SDL_Color{0, 0, 255, 255}, // blue
    };

    SDL_Color tokenize(string &s)
    {
        if (s.empty())
            return;

        if (INSTRUCTION_LIST.contains(s))
            return Colors::INSTRUCTION;
        else if (s == LINE_START)
            return Colors::START_OF_LINE;
        else
            return Colors::DEFAULT;
    }

    class Word
    {
        string word;
        SDL_Color color;

        Word() {}

    public:
        void push_back(char c)
        {
            word.push_back(c);
            color = tokenize(word);
        }
        void pop()
        {
            if (word.empty())
                return;

            word.pop();
            color = tokenize(word);
        }

        auto render(TTF_Font *font, SDL_Renderer *renderer, physics::Vector2d &&position)
        {
            auto &&[x, y] = position;

            word.push_back(" "); // adding space just for rendering
            SDL_Surface *textSurface = TTF_RenderText_Blended(font, word.c_str(), color);
            word.pop();

            if (!textSurface)
                cerr << "Error loading surface for a word!" << endl;

            auto textW = textSurface->w;
            auto textH = textSurface->h;
            texture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_Rect dstRect = {x, y, textW, textH};

            SDL_FreeSurface(textSurface);
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_DestroyTexture(texture);

            return std::make_pair(textW, textH);
        }
    };

}