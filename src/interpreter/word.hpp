#pragma once // header guard

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <utility>

namespace interpreter
{

    class Word
    {
        SDL_Color color;
        std::string word;

        void tokenize();

    public:
        Word();

        uint size() const;
        bool empty();
        const std::string &getWord() const { return word; }
        void push_back(char c);
        void pop_back();

        std::pair<int, int> render(TTF_Font *font, SDL_Renderer *renderer, int x, int y) const;
    };
}
