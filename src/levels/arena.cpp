#include "arena.hpp"
#include "prefabs/prefabs.hpp"

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

    void Arena::populateArenaWithAsteroids(int x, int y)
    {

        auto collisionPresent = []<typename Collidable>(CollisionObject *obj, vector<Collidable *> othObjects)
        {
            SDL_Rect a = obj->getDstrect();
            for (const auto &object : othObjects)
            {
                SDL_Rect b = object->getDstrect();

                if (SDL_HasIntersection(&a, &b))
                    return true;
            }
            return false;
        };
        SDL_Rect playerRect = controledObject->getDstrect();

        for (int i = 0; i < 10;)
        {
            int p = getRandomNumber(0, 100);
            const prefabs::Prefab &prefab = p > 75 ? prefabs::asteroidBig2 : (p > 40 ? prefabs::asteroid2 : prefabs::asteroid3);

            double xx = x + getRandomNumber(-1200, +1200);
            double yy = y + getRandomNumber(-1200, +1200);

            double velX = getRandomNumber<double>(-2.5, 2.5);
            double velY = getRandomNumber<double>(-2.5, 2.5);

            CollisionObject *obj = new CollisionObject{prefab, {xx, yy}, {velX, velY}};
            SDL_Rect b = obj->getDstrect();
            b = physics::expandRectangle(b, 100);

            bool playerCollision = SDL_HasIntersection(&playerRect, &b);

            if (collisionPresent(obj, collidableObjects) || collisionPresent(obj, hostileShips) || playerCollision)
            {
                printf("Collision was present, rolling new obj\n");
                delete (obj);
                continue;
            }
            collidableObjects.push_back(obj);
            ++i;
        }
    }

    Arena::Arena() //: console{gRenderer, getconsoleRect()}
    {
        viewport.h = SCREEN_HEIGHT;
        viewport.w = SCREEN_WIDTH;
        viewport.x = 0;
        viewport.y = 0;

        double x = 4000;
        double y = 4000;

        hostileShips.push_back(new ships::HostileShip(prefabs::wolf, prefabs::torpedo, {4700, 4700}));
        // hostileShips.push_back(new ships::HostileShip(prefabs::wolf, prefabs::torpedo, {3400, 3300}));
        hostileShips.push_back(new ships::HostileShip(prefabs::lasher, prefabs::lasherShell, {3550, 3750}));
        // hostileShips.push_back(new ships::HostileShip(prefabs::lasher, prefabs::lasherShell, {3700, 3750}));
        hostileShips.push_back(new ships::HostileShip(prefabs::hammerhead, prefabs::hammerheadShell, {4200, 3550}));

        controledObject = new ships::Ship(prefabs::scarab, {x, y});
        populateArenaWithAsteroids(x, y);

        for (auto &object : collidableObjects)
            collisionModel.emplace(object);
        for (auto &object : hostileShips)
            collisionModel.emplace(object);

        collisionModel.emplace(controledObject);
    }

    void Arena::handleEvent(SDL_Event &event, LevelType &levelType, bool & /**/, bool & /**/)
    {
        if (not controledObject->isAlive())
        {
            SoundManager::GetInstance().switchSound();
            levelType = LevelType::GAME_OVER;
        }
        else if (hostileShips.empty())
        {
            SoundManager::GetInstance().switchSound();
            levelType = LevelType::GAME_WON;
        }
        else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
        {
            SoundManager::GetInstance().switchSound();
            levelType = LevelType::MENU;
        }

        SDL_Point p;
        SDL_GetMouseState(&p.x, &p.y);
        physics::Vector2d mousePtr{(double)p.x - SCREEN_WIDTH / 2, (double)p.y - SCREEN_HEIGHT / 2};
        double angle = physics::normalizeDegrees(physics::getVectorRotation(mousePtr) + 90);
        angle -= controledObject->getRotation();
        angle = angle > 360 ? angle - 360 : (angle < 0 ? angle + 360 : angle);

        if (abs(angle - 360) > 3 && angle > 180)
        {
            controledObject->stopRotateRight();
            controledObject->rotateLeft();
        }
        else if (abs(angle - 360) > 3 && angle < 180)
        {
            controledObject->stopRotateLeft();
            controledObject->rotateRight();
        }
        else
        {
            controledObject->stopRotateRight();
            controledObject->stopRotateLeft();
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
            controledObject->shoot();

        else if (event.type == SDL_KEYDOWN)
        {
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
            }
        }
        if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                controledObject->removeInput(physics::DIRECTION::up);
                break;
            case SDLK_d:
                controledObject->removeInput(physics::DIRECTION::right);
                break;
            case SDLK_a:
                controledObject->removeInput(physics::DIRECTION::left);
                break;
            case SDLK_s:
                controledObject->removeInput(physics::DIRECTION::down);
                break;
            }
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

    template <typename T>
    void cleanupDeadCollidables(vector<T *> &objects, CollisionModel &collisionModel)
    {
        for (unsigned int i = 0; i < objects.size(); ++i)
        {
            if (!(objects[i]->isAlive()))
            {
                collisionModel.remove(*(objects[i]));
                delete (objects[i]);
                removeVectorElement(objects, i);
            }
        }
    }

    void Arena::render()
    {
        ships::Projectile *projectile = controledObject->frameUpdate(collisionModel);

        if (projectile)
        {
            projectiles.push_back(projectile);
            collisionModel.emplace(projectile);
        }

        collisionModel.checkCollisions();

        for (auto &object : collidableObjects)
        {
            object->frameUpdate(collisionModel);
        }
        for (auto &projectile : projectiles)
        {
            projectile->frameUpdate(collisionModel);
        }

        cleanupDeadCollidables(projectiles, collisionModel);
        cleanupDeadCollidables(collidableObjects, collisionModel);
        cleanupDeadCollidables(hostileShips, collisionModel);
        // determine tactic after cleanup of asteroids etc.
        for (auto &hostileShip : hostileShips)
        {
            ships::Projectile *p = hostileShip->frameUpdate(hostileShips, collidableObjects, *controledObject, collisionModel);
            if (p)
            {
                projectiles.push_back(p);
                collisionModel.emplace(p);
            }
        }

        background.frameUpdate(controledObject->getBody().getSpeed());
        moveViewport();

        SDL_RenderClear(gRenderer);
       // SDL_RenderCopy(gRenderer, texture, NULL, NULL);
        background.renderObject(viewport);

        for (auto &object : collidableObjects)
            object->renderObject(viewport);
        for (auto &object : hostileShips)
            object->renderObject(viewport);
        for (auto &projectile : projectiles)
            projectile->renderObject(viewport);

        controledObject->renderObject(viewport);
        //   console.render();
        SDL_RenderPresent(gRenderer);
    }
    Arena::~Arena()
    {
       // SDL_DestroyTexture(texture);

        delete (controledObject);

        for (auto *obj : projectiles)
            delete (obj);
        for (auto *obj : hostileShips)
            delete (obj);
        for (auto *obj : collidableObjects)
            delete (obj);
    }
} // namespace levels