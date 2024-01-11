
#include "menu.hpp"
#include "../sdl.hpp"

namespace levels
{
    Menu::Menu() : continueButton{"Continue", {buttonX, buttonY, buttonW, buttonH}},
                   newGameButton{"New Game", {buttonX, buttonY + buttonH + 10, buttonW, buttonH}},
                   quitButton{"Quit", {buttonX, buttonY + buttonH * 2 + 10 * 2, buttonW, buttonH}}
    {
    }

    void Menu::handleEvent(SDL_Event &event, LevelType &levelType, bool &quit, bool &newGame)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_Point p;
            SDL_GetMouseState(&p.x, &p.y);
            if (continueButton.isInside(p))
            {
                levelType = LevelType::ARENA;
            }
            else if (quitButton.isInside(p))
            {
                quit = true;
            }
            else if (newGameButton.isInside(p))
            {
                levelType = LevelType::ARENA;
                newGame = true;
            }
        }
    }

    void Menu::render()
    {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
        SDL_RenderClear(gRenderer);
        SDL_Rect fakeViewport{3000, 3000, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT};
        background.renderObject(fakeViewport);
        continueButton.renderButton();
        newGameButton.renderButton();
        quitButton.renderButton();
        SDL_RenderPresent(gRenderer);
    }
} // namespace levels
