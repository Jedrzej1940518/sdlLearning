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

    const string path = "../data/graphics/backgrounds/background3.jpg";
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
        controledObject->getBody().accelerate(getDirectionFromSdl(event.key.keysym.sym));
    }
}
void Arena::moveViewport()
{
    auto &body = controledObject->getBody();
    auto pos = body.getPosition();
    int w = controledObject->getWidth();
    int h = controledObject->getHeight();

    auto screenCenter = calculatePosition(pos, {-WINDOW_WIDTH / 2 + w / 2, -WINDOW_HEIGHT / 2 + h / 2});
    setPosition(viewport, screenCenter);
    controledObject->getBody().printBody();
}

void Arena::render()
{
    static Object asteroid{"../data/graphics/asteroids/asteroid_big02.png", {800, 800}};

    moveViewport();
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, texture, NULL, NULL);
    ship.frameUpdate(viewport);
    asteroid.frameUpdate(viewport);
    SDL_RenderPresent(gRenderer);
}
} // namespace levels