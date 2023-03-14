#pragma once

#include "sdl.hpp"

class Clock
{
    uint32_t frameRate;
    uint32_t startTime{0};

public:
    Clock(uint32_t framesPerSecond) : frameRate{static_cast<uint32_t>(1000. / framesPerSecond)}
    {
    }
    void tick()
    {
        startTime = SDL_GetTicks();
    }
    void tock()
    {
        uint32_t elapsedTime = SDL_GetTicks() - startTime;
        if (elapsedTime < frameRate)
        {
            SDL_Delay(frameRate - elapsedTime);
        }
    }
};