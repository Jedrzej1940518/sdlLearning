
#include "gameState.hpp"
#include "levels/arena.hpp"
#include "levels/menu.hpp"
#include "soundManager.hpp"

void GameState::handleEvent(SDL_Event &event, bool &quit, bool &newGame)
{
    if (!currentLevel)
        cerr << "Handling events::current level is nullptr\n";

    currentLevel->handleEvent(event, levelType, quit, newGame);

    if (newGame)
    {
        delete (arena);
        arena = new levels::Arena();
        newGame = false;
    }
    switch (levelType)
    {
    case LevelType::MENU:
        currentLevel = &menu;
        break;
    case LevelType::ARENA:
        currentLevel = arena;
        break;
    case LevelType::GAME_OVER:
        currentLevel = &gameLost;
        break;
    case LevelType::GAME_WON:
        currentLevel = &gameWon;
        break;
    }
}
void GameState::render()
{
    if (!currentLevel)
        cerr << "rendering::current level is nullptr\n";

    currentLevel->render();
}