#include "arena.hpp"

namespace levels
{

Arena::Arena()
{
    viewport.h = WINDOW_HEIGHT;
    viewport.w = WINDOW_WIDTH;
    viewport.x = 0;
    viewport.y = 0;

    // asteroid
    collidableObjects.push_back(
        {"../data/graphics/asteroids/asteroid_big02.png", "asteroid", {{800, 800}, {0, 0}, {1, 1}, 0}});

    collidableObjects.push_back(
        {"../data/graphics/asteroids/asteroid_big02.png", "asteroid", {{1200, 1200}, {0, 0}, {1, 1}, 0}});

    collidableObjects.push_back(
        {"../data/graphics/asteroids/asteroid_big02.png", "asteroid", {{300, 300}, {+1, +1}, {1, 1}, 0}});

    // ship
    collidableObjects.push_back(
        {"../data/graphics/ships/scarab.png", "scarab", physics::Body{{500, 500}, {0, 0}, {10, 10}, 0.5}});

    controledObject = &collidableObjects.back();

    for (auto &object : collidableObjects)
        object.getGridPosition() = collisionModel.emplace(&object);
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
    Vector2d offset{static_cast<double>(-(WINDOW_WIDTH / 2.) + w / 2.),
                    static_cast<double>(-(WINDOW_HEIGHT / 2.) + h / 2.)};

    SDL_Point screenCenter = calculatePosition(SDL_Point{x, y}, offset);
    setPosition(viewport, screenCenter);

    controledObject->printPosition();
    controledObject->printSpeed();
    controledObject->printGridPosition();
}

void Arena::render()
{

    for (auto &object : collidableObjects)
    {
        object.frameUpdate();
        collisionModel.recalculateGridPosition(object);
    }
    collisionModel.checkCollisions();

    background.frameUpdate(controledObject->getBody().getSpeed());
    moveViewport();

    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, texture, NULL, NULL);
    background.renderObject(viewport);

    for (auto &object : collidableObjects)
        object.renderObject(viewport);

    SDL_RenderPresent(gRenderer);
}
} // namespace levels