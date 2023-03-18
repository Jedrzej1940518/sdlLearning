
#include "chatbox.hpp"

namespace rendering
{

// class Carousel
// {

// };

void Chatbox::render()
{
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &dstrect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &dstrect);

    // SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void Chatbox::handleEvents(SDL_Event &event)
{
    // lines[(text, event.text.text);
}

Chatbox::Chatbox(SDL_Renderer *renderer, SDL_Rect dstrect) : renderer{renderer}, dstrect{dstrect}
{
}

} // namespace rendering