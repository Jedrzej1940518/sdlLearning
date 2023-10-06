#include "word.hpp"
#include "instructions.hpp"

namespace interpreter
{
    Word::Word() : color{colors::INSTRUCTION}, word{} {}

    void Word::tokenize()
    {
        if (INSTRUCTION_LIST.contains(word))
            color = colors::INSTRUCTION;
        else if (word == LINE_START)
            color = colors::START_OF_LINE;
        else
            color = colors::DEFAULT;
    }

    uint Word::size() const
    {
        return word.size();
    }

    bool Word::empty()
    {
        return word.empty();
    }

    void Word::push_back(char c)
    {
        word.push_back(c);
        tokenize();
    }

    void Word::pop_back()
    {
        if (word.empty())
            return;

        word.pop_back();
        tokenize();
    }

    std::pair<int, int> Word::render(TTF_Font *font, SDL_Renderer *renderer, int x, int y) const
    {
        string renderedWord = word + ' '; // adding space after every word just for rendering

        SDL_Surface *textSurface = TTF_RenderText_Blended(font, renderedWord.c_str(), color);

        if (!textSurface)
            std::cerr << "Error loading surface for a word!" << std::endl;

        auto textW = textSurface->w;
        auto textH = textSurface->h;

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect dstRect = {x, y, textW, textH};

        SDL_FreeSurface(textSurface);
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
        SDL_DestroyTexture(texture);

        return std::make_pair(textW, textH);
    }
}
