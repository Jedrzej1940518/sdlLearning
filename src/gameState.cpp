
#include "gameState.hpp"
// #include "levels/arena.hpp"
#include "levels/menu.hpp"
#include "soundManager.hpp"

void GameState::handleEvents()
{
    if (!currentLevel)
        std::cerr << "Handling events::current level is nullptr\n";

    sf::Event event;
    while (window.pollEvent(event))
        currentLevel->handleEvents(event);

    // if (newGame)
    // {
    //     delete (arena);
    //     arena = new levels::Arena();
    //     newGame = false;
    // }
    switch (levelType)
    {
    case levels::LevelType::MENU:
        currentLevel = &menu;
        break;
    case levels::LevelType::ARENA:
        currentLevel = arena;
        break;
        // case LevelType::GAME_OVER:
        //     currentLevel = &gameLost;
        //     break;
        // case LevelType::GAME_WON:
        //     currentLevel = &gameWon;
        //     break;
    }
}
void GameState::render()
{
    if (!currentLevel)
        std::cerr << "rendering::current level is nullptr\n";

    currentLevel->render();
}