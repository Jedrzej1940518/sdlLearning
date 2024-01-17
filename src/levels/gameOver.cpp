
#include "gameOver.hpp"
#include "mySdl.hpp"

namespace levels
{
    GameOver::GameOver(string &&title) : text{std::move(title), {buttonX - buttonW, buttonY - 6 * buttonH, 3 * buttonW, 3 * buttonH}, SDL_Color{255, 255, 0, 255}},
                                         playAgainButton{"Play Again", {buttonX, buttonY, buttonW, buttonH}},
                                         quitButton{"Quit", {buttonX, buttonY + buttonH + 10, buttonW, buttonH}}
    {
    }

    void GameOver::handleEvents(SDL_Event &event, LevelType &levelType, bool &quit, bool &newGame)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_Point p;
            SDL_GetMouseState(&p.x, &p.y);
            if (playAgainButton.isInside(p))
            {
                SoundManager::GetInstance().switchSound();
                newGame = true;
                levelType = LevelType::ARENA;
            }
            else if (quitButton.isInside(p))
            {
                quit = true;
            }
        }
    }

    void GameOver::render()
    {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
        SDL_RenderClear(gRenderer);
        SDL_Rect fakeViewport{3000, 3000, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT};
        background.renderObject(fakeViewport);
        text.renderText();
        playAgainButton.renderButton();
        quitButton.renderButton();
        SDL_RenderPresent(gRenderer);
    }
} // namespace levels
