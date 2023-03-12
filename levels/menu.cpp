
#include "../sdl.hpp"
#include "menu.hpp"

using namespace utils;

namespace levels::menu
{
    Button Menu::newGameButton{"New Game", {100, 10, 100, 50}};
    Button Menu::quitButton{"Quit", {100, 110, 100, 50}};

    void Menu::handleEvent(const SDL_Event &event, Level &level, bool &quit)
    {
        renderMenu();

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_Point p;
            SDL_GetMouseState(&p.x, &p.y);
            if (newGameButton.isInside(p))
            {
                level = Level::ARENA;
            }
            else if (quitButton.isInside(p))
            {
                quit = true;
            }
        }
    }

    void Menu::renderMenu()
    {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
        SDL_RenderClear(gRenderer);
        newGameButton.renderButton();
        quitButton.renderButton();
        SDL_RenderPresent(gRenderer);
    }
}
