
#include "utils.hpp"
#include "gameState.hpp"
// #include "soundManager.hpp"

int main(int argc, char **argv)
{
    globals::WINDOW = new sf::RenderWindow (sf::VideoMode(config::SCREEN_WIDTH, config::SCREEN_HEIGHT), "My window");
    globals::WINDOW->setFramerateLimit(config::FRAME_RATE);

    // globals::WINDOW->setVerticalSyncEnabled(true);
    GameState gameState{};

    while (globals::WINDOW->isOpen())
    {

        gameState.handleEvents();
        gameState.render();
  
        // SoundManager::GetInstance().cleanupDeadSounds();

    }

    return 1;
}
