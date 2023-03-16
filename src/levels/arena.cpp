#include "arena.hpp"

namespace levels
{

Arena::Arena()
{
    viewport.h = WINDOW_HEIGHT;
    viewport.w = WINDOW_WIDTH;
    viewport.x = 0;
    viewport.y = 0;

    //    const string path = "../data/graphics/backgrounds/background3.jpg";
    //    texture = loadTexture(path);
}

void Arena::handleEvent(const SDL_Event &event, LevelType &levelType, bool & /**/)
{
    if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
    {
        levelType = LevelType::MENU;
    }
    else if (event.type == SDL_KEYDOWN)
    {
        controledObject->getBody().accelerate(getDirectionFromSdl(event.key.keysym.sym));
    }
    else if (event.type == SDL_KEYUP)
    {
        controledObject->getBody().deaccelerate(getDirectionFromSdl(event.key.keysym.sym));
    }
}
void Arena::moveViewport()
{
    int x = controledObject->getX();
    int y = controledObject->getY();
    int w = controledObject->getWidth();
    int h = controledObject->getHeight();
    Vector2d offset{static_cast<double>(-WINDOW_WIDTH / 2. + w / 2.),
                    static_cast<double>(-WINDOW_HEIGHT / 2. + h / 2.)};

    SDL_Point screenCenter = calculatePosition(SDL_Point{x, y}, offset);
    setPosition(viewport, screenCenter);
    controledObject->getBody().printBody();
}

void Arena::render()
{
    static rendering::Object asteroid{"../data/graphics/asteroids/asteroid_big02.png", {800, 800}};

    ship.frameUpdate();
    background.frameUpdate(controledObject->getBody().getSpeed());
    moveViewport();

    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, texture, NULL, NULL);
    background.renderObject(viewport);
    ship.renderObject(viewport);
    asteroid.renderObject(viewport);
    SDL_RenderPresent(gRenderer);
}
} // namespace levels