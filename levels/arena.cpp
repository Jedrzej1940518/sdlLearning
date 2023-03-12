#include "arena.hpp"

namespace levels::arena
{

    Arena::Arena()
    {

        SDL_Surface *surface = IMG_Load("../data/stars.webp");
        SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, surface);
        SDL_FreeSurface(surface);
    }
    void Arena::handleEvent(const SDL_Event &event, Level &level)
    {

        renderArena();

        if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
        {
            level = Level::MENU;
        }
    }
    void Arena::renderArena()
    {
        SDL_RenderCopy(gRenderer, texture, NULL, NULL);
    }
}