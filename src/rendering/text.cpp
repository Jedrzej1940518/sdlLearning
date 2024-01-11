#include "text.hpp"

namespace rendering
{

    Text::Text(string &&text, SDL_Rect &&position, SDL_Color &&color) : text{text}, position{position}, color{color}
    {
        SDL_Surface *textSurface = TTF_RenderText_Blended(gBigFont, text.c_str(), color);

        if (!textSurface)
            cerr << "Error loading font!" << endl;

        textW = textSurface->w;
        textH = textSurface->h;

        texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

        SDL_FreeSurface(textSurface);
    }
    void Text::renderText()
    {
        SDL_Rect textRectangle = {position.x + position.w / 2 - textW / 2, position.y + position.h / 2 - textH / 2, textW,
                                  textH};

        SDL_RenderCopy(gRenderer, texture, NULL, &textRectangle);
    }
}