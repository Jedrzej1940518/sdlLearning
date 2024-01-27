
#include <SFML/Graphics.hpp>


#include "utils.hpp"
#include "gameState.hpp"
// #include "soundManager.hpp"

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(config::SCREEN_WIDTH, config::SCREEN_HEIGHT), "My window");
    window.setFramerateLimit(config::FRAME_RATE);
    // window.setVerticalSyncEnabled(true);
    GameState gameState{window};

    while (window.isOpen())
    {
        gameState.handleEvents();
        gameState.render();
  
        // SoundManager::GetInstance().cleanupDeadSounds();

    }

    return 1;
}
