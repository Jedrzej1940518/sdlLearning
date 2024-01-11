#include "clock.hpp"
#include "gameState.hpp"
#include "sdl.hpp"
#include "soundManager.hpp"

int main()
{
    bool quit = not initSdl(); // if init failed, quit
    bool newGame = false;
    GameState gameState{};
    Clock clock{FRAME_RATE};

    SDL_Event event;

    while (not quit)
    {
        clock.tick();
        while (SDL_PollEvent(&event))
        {
            gameState.handleEvent(event, quit, newGame);
        }
        gameState.render();
        clock.tock();
    }
    cleanSdl();
}
