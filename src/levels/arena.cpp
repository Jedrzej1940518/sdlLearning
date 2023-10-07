#include "arena.hpp"
#include "../prefabs/prefabs.hpp"

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

    Arena::Arena() : chatbox{gRenderer, getChatboxRect()}
    {
        viewport.h = SCREEN_HEIGHT;
        viewport.w = SCREEN_WIDTH;
        viewport.x = 0;
        viewport.y = 0;

        collidableObjects.push_back({prefabs::asteroidBig2, {5000, 5000}});
        collidableObjects.push_back({prefabs::asteroid2, {5500, 5500}});
        collidableObjects.push_back({prefabs::asteroid3, {4500, 4500}});
        collidableObjects.push_back({prefabs::scarab, {4000, 4000}});

        // collidableObjects.push_back(
        //     {"../data/graphics/asteroids/asteroid_big02.png", "asteroid1", {5000, 5000}, {500, {0, 0}, 2, 0, 10, 0}});

        // collidableObjects.push_back(
        //     {"../data/graphics/asteroids/asteroid2.png", "asteroid2", {5500, 5500}, {100, {0, 0}, 2, 0, 10, 0}});

        // collidableObjects.push_back(
        //     {"../data/graphics/asteroids/asteroid3.png", "asteroid3", {4500, 4500}, {200, {0, 0}, 2, 0, 10, 0}});

        // collidableObjects.push_back(
        //     {"../data/graphics/ships/scarab.png", "scarab", {4000, 4000}, {100, {0, 0}, 7, 0.03, 2, 0}});

        controledObject = &collidableObjects.back();
        chatbox.setControledObject(controledObject);

        for (auto &object : collidableObjects)
            collisionModel.emplace(&object);
    }

    void Arena::handleEvent(SDL_Event &event, LevelType &levelType, bool & /**/)
    {
        if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
        {
            levelType = LevelType::MENU;
        }

        chatbox.handleEvent(event);
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