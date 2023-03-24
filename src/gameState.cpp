
#include "gameState.hpp"
#include "levels/arena.hpp"
#include "levels/menu.hpp"

void GameState::handleEvent(SDL_Event &event, bool &quit)
{
    switch (levelType)
    {
    case LevelType::MENU:
        currentLevel = &menu;
        break;
    case LevelType::ARENA:
        currentLevel = &arena;
        break;
    }
    if (!currentLevel)
        cerr << "Handling events::current level is nullptr\n";

    currentLevel->handleEvent(event, levelType, quit);
}
void GameState::render()
{
    if (!currentLevel)
        cerr << "rendering::current level is nullptr\n";

    currentLevel->render();
}