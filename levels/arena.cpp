#include "arena.hpp"
#include "../object.hpp"

namespace levels
{

    Arena::Arena()
    {
        viewport.h = WINDOW_HEIGHT;
        viewport.w = WINDOW_WIDTH;
        viewport.x = 0;
        viewport.y = 0;

        const string path = "data/graphics/backgrounds/background3.jpg";
        texture = loadTexture(path);
    }

    void Arena::handleEvent(const SDL_Event &event, LevelType &levelType, bool & /**/)
    {
        if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
        {
            levelType = LevelType::MENU;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            controledObject->accelerate(getDirectionFromSdl(event.key.keysym.sym));
        }
    
            
    }
    void Arena::moveViewport()
    {
        controledObject->getPosition();
        setPosition(viewport, controledObject->getPosition());
    }

    void Arena::render()
    {
        static Object asteroid{"data/graphics/asteroids/asteroid_big02.png", {1200, 1200}};

        moveViewport();
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, texture, NULL, NULL);
        ship.frameUpdate(viewport);
        asteroid.frameUpdate(viewport);
        SDL_RenderPresent(gRenderer);
    }
}