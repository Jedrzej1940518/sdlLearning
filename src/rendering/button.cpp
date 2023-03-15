#include "button.hpp"

namespace rendering
{

Button::Button(string text, SDL_Rect position) : text{text}, position{position}
{
    SDL_Surface *textSurface = TTF_RenderText_Blended(gFont, text.c_str(), textColor);

    if (!textSurface)
        cerr << "Error loading font!" << endl;

    textW = textSurface->w;
    textH = textSurface->h;

    texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_FreeSurface(textSurface);
}

void Button::renderButton()
{
    SDL_SetRenderDrawColor(gRenderer, 128, 128, 128, 255);
    SDL_RenderFillRect(gRenderer, &position);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(gRenderer, &position);

    SDL_Rect textRectangle = {position.x + position.w / 2 - textW / 2, position.y + position.h / 2 - textH / 2, textW,
                              textH};

    SDL_RenderCopy(gRenderer, texture, NULL, &textRectangle);
}

bool Button::isInside(const SDL_Point &p)
{
    return (p.x >= position.x && p.x <= position.x + position.w && p.y >= position.y && p.y <= position.y + position.h);
}

} // namespace rendering