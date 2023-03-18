#include "arena.hpp"

namespace levels
{

Arena::Arena()
{
    viewport.h = WINDOW_HEIGHT;
    viewport.w = WINDOW_WIDTH;
    viewport.x = 0;
    viewport.y = 0;

    collidableObjects.push_back({"../data/graphics/asteroids/asteroid_big02.png",
                                 "asteroid",
                                 {5000, 5000},
                                 physics::Body{{0, 0}, {1, 1}, 0},
                                 collisionModel});

    collidableObjects.push_back({"../data/graphics/asteroids/asteroid_big02.png",
                                 "asteroid",
                                 {5500, 5500},
                                 physics::Body{{0, 0}, {1, 1}, 0},
                                 collisionModel});

    collidableObjects.push_back({"../data/graphics/asteroids/asteroid_big02.png",
                                 "asteroid",
                                 {4500, 4500},
                                 physics::Body{{+1, +1}, {1, 1}, 0},
                                 collisionModel});

    collidableObjects.push_back({"../data/graphics/ships/scarab.png",
                                 "scarab",
                                 {4000, 4000},
                                 physics::Body{{0, 0}, {10, 10}, 0.5},
                                 collisionModel});

    controledObject = &collidableObjects.back();
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
        object.frameUpdate();

    collisionModel.checkCollisions();

    background.frameUpdate(controledObject->getBody().getSpeed());
    background.printPosition();
    moveViewport();

    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, texture, NULL, NULL);
    background.renderObject(viewport);

    for (auto &object : collidableObjects)
        object.renderObject(viewport);

    SDL_RenderPresent(gRenderer);
}
} // namespace levels