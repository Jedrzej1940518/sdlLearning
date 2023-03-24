
#include "chatbox.hpp"
#include <iostream>

namespace rendering
{

// class Carousel
// {

// };

void Chatbox::renderText()
{
    for (int i = 0; i < static_cast<int>(lines.size()); ++i)
    {
        SDL_Surface *textSurface = TTF_RenderText_Blended(font, lines[i].c_str(), textColor);

        if (!textSurface)
            cerr << "Error loading font for chatbox!" << endl;

        auto textW = textSurface->w;
        auto textH = textSurface->h;

        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
        SDL_Rect textDstRect = {dstrect.x + 20, dstrect.y + dstrect.h - textH * (i + 1), textW, textH};
        SDL_RenderCopy(renderer, texture, NULL, &textDstRect);
    }
}

void Chatbox::render()
{
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &dstrect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &dstrect);

    renderText();
}

void Chatbox::handleEvent(SDL_Event &event, bool & /**/)
{
    if (event.type == SDL_TEXTINPUT)
    {
        lines[0] += event.text.text;
    }
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_KP_ENTER)
    {
        lines[1] = lines[0];
        lines[0] = "";
    }
}

Chatbox::Chatbox(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect dstrect)
    : renderer{renderer}, font{font}, dstrect{dstrect}
{
    lines[0] = "xx ";
    lines[1] = "xx1 ";
}

} // namespace rendering