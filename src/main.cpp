// #include "clock.hpp"
#include "gameState.hpp"
// #include "mySdl.hpp"
// #include "soundManager.hpp"

#include <SFML/Graphics.hpp>
#include "utils.hpp"

int main(int argc, char **argv)
{
    // Clock clock{FRAME_RATE};

    // SDL_Event event;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My window");
    window.setFramerateLimit(60);
    // window.setVerticalSyncEnabled(true);
    GameState gameState{window};

    while (window.isOpen())
    {
        gameState.handleEvents();
        gameState.render();

        // clock.tick();
        // do
        // {
        // } while (SDL_PollEvent(&event));

        // SoundManager::GetInstance().cleanupDeadSounds();
        // clock.tock();
    }
    // cleanSdl();
    return 1;
}
