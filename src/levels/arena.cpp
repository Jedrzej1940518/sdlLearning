#include "arena.hpp"

namespace levels
{

    using namespace physics; // todo remove this
    SDL_Rect getChatboxRect()
    {
        int w = SCREEN_WIDTH / 2;
        int h = SCREEN_HEIGHT / 4;
        int x = SCREEN_WIDTH / 2 - w / 2;
        int y = SCREEN_HEIGHT - h;

        return {x, y, w, h};
    }

    Arena::Arena() : chatbox{gRenderer, gFont, getChatboxRect()}
    {
        viewport.h = SCREEN_HEIGHT;
        viewport.w = SCREEN_WIDTH;
        viewport.x = 0;
        viewport.y = 0;

        collidableObjects.push_back(
            {"../data/graphics/asteroids/asteroid_big02.png", "asteroid1", {5000, 5000}, {500, {0, 0}, {2, 2}, 0}});

        collidableObjects.push_back(
            {"../data/graphics/asteroids/asteroid2.png", "asteroid2", {5500, 5500}, {100, {0, 0}, {2, 2}, 0}});

        collidableObjects.push_back(
            {"../data/graphics/asteroids/asteroid3.png", "asteroid3", {4500, 4500}, {200, {0, 0}, {2, 2}, 0}});

        collidableObjects.push_back(
            {"../data/graphics/ships/scarab.png", "scarab", {4000, 4000}, {100, {0, 0}, {10, 10}, 0.5}});

        controledObject = &collidableObjects.back();

        for (auto &object : collidableObjects)
            collisionModel.emplace(&object);
    }

    void Arena::handleEvent(SDL_Event &event, LevelType &levelType, bool & /**/)
    {
        static bool debug = true;

        if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
        {
            levelType = LevelType::MENU;
        }

        chatbox.handleEvent(event, debug);

        if (event.type == SDL_KEYDOWN && debug)
        {
            controledObject->getBody().accelerate(getDirectionFromSdl(event.key.keysym.sym));
        }
        else if (event.type == SDL_KEYUP && debug)
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
        Vector2d offset{static_cast<double>(-(SCREEN_WIDTH / 2.) + w / 2.),
                        static_cast<double>(-(SCREEN_HEIGHT / 2.) + h / 2.)};

        SDL_Point screenCenter = calculatePosition(SDL_Point{x, y}, offset);
        setPosition(viewport, screenCenter);
    }

    void Arena::render()
    {

        for (auto &object : collidableObjects)
        {
            object.frameUpdate(collisionModel);
        }
        collisionModel.checkCollisions();

        background.frameUpdate(controledObject->getBody().getSpeed());
        moveViewport();

        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, texture, NULL, NULL);
        background.renderObject(viewport);

        for (auto &object : collidableObjects)
            object.renderObject(viewport);
        chatbox.render();
        SDL_RenderPresent(gRenderer);
    }
} // namespace levels