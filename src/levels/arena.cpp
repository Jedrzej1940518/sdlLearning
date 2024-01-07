#include "arena.hpp"
#include "../prefabs/prefabs.hpp"

namespace levels
{

    using namespace physics; // todo remove this
    SDL_Rect getconsoleRect()
    {
        int w = SCREEN_WIDTH / 2;
        int h = SCREEN_HEIGHT / 4;
        int x = SCREEN_WIDTH / 2 - w / 2;
        int y = SCREEN_HEIGHT - h;

        return {x, y, w, h};
    }

    Arena::Arena() //: console{gRenderer, getconsoleRect()}
    {
        viewport.h = SCREEN_HEIGHT;
        viewport.w = SCREEN_WIDTH;
        viewport.x = 0;
        viewport.y = 0;

        // collidableObjects.push_back({prefabs::asteroidBig2, {5000, 5000}});
        // collidableObjects.push_back({prefabs::asteroid2, {5500, 5500}});
        collidableObjects.push_back(new CollisionObject(prefabs::asteroid3, {4500, 4500}));
        controledObject = new ships::Ship(prefabs::scarab, {4000, 4000});

        collidableObjects.push_back(controledObject);

        // console.setControledObject(controledObject);

        for (auto &object : collidableObjects)
            collisionModel.emplace(object);
    }

    void Arena::handleEvent(SDL_Event &event, LevelType &levelType, bool & /**/)
    {
        if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
        {
            levelType = LevelType::MENU;
        }
        if (event.type == SDL_KEYDOWN)
        {
            LOG("event: %d", event.key.keysym.sym);

            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                controledObject->addInput(physics::DIRECTION::up);
                break;
            case SDLK_d:
                controledObject->addInput(physics::DIRECTION::right);
                break;
            case SDLK_a:
                controledObject->addInput(physics::DIRECTION::left);
                break;
            case SDLK_s:
                controledObject->addInput(physics::DIRECTION::down);
                break;
            case SDLK_q:
                controledObject->rotateLeft();
                break;
            case SDLK_e:
                controledObject->rotateRight();
                break;
            }
        }

        // console.handleEvent(event);
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
            collisionModel.checkCollisions(*object);
        }
        controledObject->frameUpdate();
        for (auto &object : collidableObjects)
        {
            object->frameUpdate(collisionModel);
        }

        background.frameUpdate(controledObject->getBody().getSpeed());
        moveViewport();

        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, texture, NULL, NULL);
        background.renderObject(viewport);

        for (auto &object : collidableObjects)
            object->renderObject(viewport);
        //   console.render();
        SDL_RenderPresent(gRenderer);
    }
} // namespace levels