#include "sdl.hpp"
#include "eventHandling.hpp"

int main()
{
    sdl::initSdl();

    bool quit{false};
    SDL_Event event;

    while (not quit)
    {
        while (SDL_PollEvent(&event))
        {
            eventHandling::handleEvent(event, quit);
        }
    }
    sdl::cleanSdl();
}
