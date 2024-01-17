#include "arena.hpp"
// #include "prefabs/prefabs.hpp"

namespace levels
{

    // SDL_Rect getconsoleRect()
    // {
    //     int w = SCREEN_WIDTH / 2;
    //     int h = SCREEN_HEIGHT / 4;
    //     int x = SCREEN_WIDTH / 2 - w / 2;
    //     int y = SCREEN_HEIGHT - h;

    //     return {x, y, w, h};
    // }

    // void Arena::populateArenaWithAsteroids(int x, int y)
    // {

    //     auto collisionPresent = []<typename Collidable>(CollisionObject *obj, vector<Collidable *> othObjects)
    //     {
    //         SDL_Rect a = obj->getDstrect();
    //         for (const auto &object : othObjects)
    //         {
    //             SDL_Rect b = object->getDstrect();

    //             if (SDL_HasIntersection(&a, &b))
    //                 return true;
    //         }
    //         return false;
    //     };
    //     SDL_Rect playerRect = controledObject->getDstrect();

    //     for (int i = 0; i < 10;)
    //     {
    //         int p = getRandomNumber(0, 100);
    //         const prefabs::Prefab &prefab = p > 75 ? prefabs::asteroidBig2 : (p > 40 ? prefabs::asteroid2 : prefabs::asteroid3);

    //         double xx = x + getRandomNumber(-1200, +1200);
    //         double yy = y + getRandomNumber(-1200, +1200);

    //         double velX = getRandomNumber<double>(-2.5, 2.5);
    //         double velY = getRandomNumber<double>(-2.5, 2.5);

    //         CollisionObject *obj = new CollisionObject{prefab, {xx, yy}, {velX, velY}};
    //         SDL_Rect b = obj->getDstrect();
    //         b = physics::expandRectangle(b, 100);

    //         bool playerCollision = SDL_HasIntersection(&playerRect, &b);

    //         if (collisionPresent(obj, collidableObjects) || collisionPresent(obj, hostileShips) || playerCollision)
    //         {
    //             printf("Collision was present, rolling new obj\n");
    //             delete (obj);
    //             continue;
    //         }
    //         collidableObjects.push_back(obj);
    //         ++i;
    //     }
    // }

    Arena::Arena(sf::RenderWindow &window, LevelType &level) : Level{window, level} //: console{gRenderer, getconsoleRect()}
    {
        auto background = std::make_shared<rendering::Object>(prefabs::background);
        auto player = std::make_shared<ships::Ship>(prefabs::scarab, sf::Vector2f{1250, 1250});
        auto asteroid1 = std::make_shared<rendering::CollisionObject>(prefabs::asteroid3, sf::Vector2f{1100, 1100}, sf::Vector2f{1.f, -1.f});
        auto asteroid2 = std::make_shared<rendering::CollisionObject>(prefabs::asteroidBig2, sf::Vector2f{1400, 1400}, sf::Vector2f{1.f, 1.f});

        objects = {background, player, asteroid1, asteroid2};
        collidables = {player, asteroid1, asteroid2};
        controledObject = player;

        for (auto &object : collidables)
            collisionModel.emplace(*object); // weird that i use shared_ptr and normal ptr?

        // viewport.h = SCREEN_HEIGHT;
        // viewport.w = SCREEN_WIDTH;
        // viewport.x = 0;
        // viewport.y = 0;

        // double x = 4000;
        // double y = 4000;

        // hostileShips.push_back(new ships::HostileShip(prefabs::wolf, prefabs::torpedo, {4700, 4700}));
        // hostileShips.push_back(new ships::HostileShip(prefabs::wolf, prefabs::torpedo, {3400, 3300}));
        // hostileShips.push_back(new ships::HostileShip(prefabs::lasher, prefabs::lasherShell, {3550, 3750}));
        // hostileShips.push_back(new ships::HostileShip(prefabs::lasher, prefabs::lasherShell, {3700, 3750}));
        // hostileShips.push_back(new ships::HostileShip(prefabs::hammerhead, prefabs::hammerheadShell, {4200, 3550}));

        // populateArenaWithAsteroids(x, y);

        // for (auto &object : hostileShips)
        //     collisionModel.emplace(object);

        // collisionModel.emplace(controledObject);
    }

    void Arena::handleEvents(const sf::Event &event)
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            window.setView(window.getDefaultView());
            level = LevelType::MENU;
        }
        else
            controledObject->handleEvents(event);

        // if (not controledObject->isAlive())
        // {
        //     SoundManager::GetInstance().switchSound();
        //     levelType = LevelType::GAME_OVER;
        //     return;
        // }
        // else if (hostileShips.empty())
        // {
        //     SoundManager::GetInstance().switchSound();
        //     levelType = LevelType::GAME_WON;
        //     return;
        // }
        // else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
        // {
        //     SoundManager::GetInstance().switchSound();
        //     levelType = LevelType::MENU;
        //     return;
        // }

        // SDL_Point p;
        // SDL_GetMouseState(&p.x, &p.y);
        // physics::Vector2d mousePtr{(double)p.x - SCREEN_WIDTH / 2, (double)p.y - SCREEN_HEIGHT / 2};
        // float angle = physics::normalizeDegrees(physics::getVectorRotation(mousePtr) + 90);
        // angle -= controledObject->getRotation();
        // angle = angle > 360 ? angle - 360 : (angle < 0 ? angle + 360 : angle);

        // if (abs(angle - 360) > 3 && angle > 180)
        // {
        //     controledObject->stopRotateRight();
        //     controledObject->rotateLeft();
        // }
        // else if (abs(angle - 360) > 3 && angle < 180)
        // {
        //     controledObject->stopRotateLeft();
        //     controledObject->rotateRight();
        // }
        // else
        // {
        //     controledObject->stopRotateRight();
        //     controledObject->stopRotateLeft();
        // }
        // if (event.type == SDL_MOUSEBUTTONDOWN)
        //     controledObject->shoot();

        // else if (event.type == SDL_KEYDOWN)
        // {
        //     switch (event.key.keysym.sym)
        //     {
        //     case SDLK_w:
        //         controledObject->addInput(physics::DIRECTION::up);
        //         break;
        //     case SDLK_d:
        //         controledObject->addInput(physics::DIRECTION::right);
        //         break;
        //     case SDLK_a:
        //         controledObject->addInput(physics::DIRECTION::left);
        //         break;
        //     case SDLK_s:
        //         controledObject->addInput(physics::DIRECTION::down);
        //         break;
        //     }
        // }
        // if (event.type == SDL_KEYUP)
        // {
        //     switch (event.key.keysym.sym)
        //     {
        //     case SDLK_w:
        //         controledObject->removeInput(physics::DIRECTION::up);
        //         break;
        //     case SDLK_d:
        //         controledObject->removeInput(physics::DIRECTION::right);
        //         break;
        //     case SDLK_a:
        //         controledObject->removeInput(physics::DIRECTION::left);
        //         break;
        //     case SDLK_s:
        //         controledObject->removeInput(physics::DIRECTION::down);
        //         break;
        //     }
        // }
    }
    // void Arena::moveViewport()
    // {
    //     // int x = controledObject->getX();
    //     // int y = controledObject->getY();
    //     // int w = controledObject->getWidth();
    //     // int h = controledObject->getHeight();
    //     // Vector2d offset{static_cast<double>(-(SCREEN_WIDTH / 2.) + w / 2.),
    //     //                 static_cast<double>(-(SCREEN_HEIGHT / 2.) + h / 2.)};

    //     // SDL_Point screenCenter = calculatePosition(SDL_Point{x, y}, offset);
    //     // setPosition(viewport, screenCenter);
    // }

    // template <typename T>
    // void cleanupDeadCollidables(vector<T *> &objects, CollisionModel &collisionModel)
    // {
    //     // for (unsigned int i = 0; i < objects.size(); ++i)
    //     // {
    //     //     if (!(objects[i]->isAlive()))
    //     //     {
    //     //         collisionModel.remove(*(objects[i]));
    //     //         delete (objects[i]);
    //     //         removeVectorElement(objects, i);
    //     //     }
    //     // }
    // }

    void Arena::frameUpdate()
    {
        collisionModel.checkCollisions();

        for (auto &obj : objects)
            obj->frameUpdate();

        collisionModel.recalculateGridPositions();

        sf::View v = window.getView();
        v.setCenter(controledObject->getSprite().getPosition());
        window.setView(v);
    }

    void Arena::draw()
    {
        for (auto &obj : objects)
            window.draw(*obj);
    }

    void Arena::render()
    {

        window.clear(sf::Color::White);

        frameUpdate();
        draw();

        window.display();

        // ships::Projectile *projectile = controledObject->frameUpdate(collisionModel);

        // if (projectile)
        // {
        //     projectiles.push_back(projectile);
        //     collisionModel.emplace(projectile);
        // }

        // collisionModel.checkCollisions();

        // for (auto &object : collidableObjects)
        // {
        //     object->frameUpdate(collisionModel);
        // }
        // for (auto &projectile : projectiles)
        // {
        //     projectile->frameUpdate(collisionModel);
        // }

        // cleanupDeadCollidables(projectiles, collisionModel);
        // cleanupDeadCollidables(collidableObjects, collisionModel);
        // cleanupDeadCollidables(hostileShips, collisionModel);
        // // determine tactic after cleanup of asteroids etc.
        // for (auto &hostileShip : hostileShips)
        // {
        //     ships::Projectile *p = hostileShip->frameUpdate(hostileShips, collidableObjects, *controledObject, collisionModel);
        //     if (p)
        //     {
        //         projectiles.push_back(p);
        //         collisionModel.emplace(p);
        //     }
        // }

        // background.frameUpdate(controledObject->getBody().getVelocity());
        // moveViewport();

        // SDL_RenderClear(gRenderer);
        // // SDL_RenderCopy(gRenderer, texture, NULL, NULL);
        // background.renderObject(viewport);

        // for (auto &object : collidableObjects)
        //     object->renderObject(viewport);
        // for (auto &object : hostileShips)
        //     object->renderObject(viewport);
        // for (auto &projectile : projectiles)
        //     projectile->renderObject(viewport);

        // controledObject->renderObject(viewport);
        // //   console.render();
        // SDL_RenderPresent(gRenderer);
    }
    Arena::~Arena()
    {
        // SDL_DestroyTexture(texture);

        // delete (controledObject);

        // for (auto *obj : projectiles)
        //     delete (obj);
        // for (auto *obj : hostileShips)
        //     delete (obj);
        // for (auto *obj : collidableObjects)
        //     delete (obj);
    }
} // namespace levels