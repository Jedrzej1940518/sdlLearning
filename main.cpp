#include "sdl.hpp"
#include "gameState.hpp"
#include "clock.hpp"


int main()
{
    constexpr uint32_t fps{30};
    
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
