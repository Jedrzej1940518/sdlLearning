#include "clock.hpp"
#include "gameState.hpp"
#include "sdl.hpp"

int main()
{
    constexpr uint fps{60};

    initSdl();

    bool quit{false};
    GameState gameState{};
    Clock clock{fps};

    SDL_Event event;

    while (not quit)
    {
        clock.tick();
        while (SDL_PollEvent(&event))
        {
            gameState.handleEvent(event, quit);
        }
        gameState.render();
        clock.tock();
    }
    cleanSdl();
}
