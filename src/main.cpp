
#include "utils.hpp"
#include "gameState.hpp"
// #include "soundManager.hpp"

int main(int argc, char **argv)
{
    initRendering();

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
