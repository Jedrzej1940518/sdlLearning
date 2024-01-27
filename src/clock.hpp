#pragma once

#include "mySdl.hpp"

class Clock
{
    unsigned int frameRate;
    unsigned int startTime{0};

public:
    Clock(unsigned int framesPerSecond) : frameRate{static_cast<unsigned int>(1000. / framesPerSecond)}
    {
    }
    void tick()
    {
        startTime = SDL_GetTicks();
    }
    void tock()
    {
        unsigned int elapsedTime = SDL_GetTicks() - startTime;
        if (elapsedTime < frameRate)
        {
            SDL_Delay(frameRate - elapsedTime);
        }
    }
};