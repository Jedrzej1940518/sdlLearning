#include "arena.hpp"
#include "rendering/background.hpp"
#include "ships/aiShip.hpp"

// #include "prefabs/prefabs.hpp"

namespace levels
{

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

    //         if (collisionPresent(obj, collidableObjects) || collisionPresent(obj, aiShips) || playerCollision)
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
        auto background = std::make_shared<rendering::Background>(prefabs::background);

        auto asteroid1 = std::make_shared<rendering::CollisionObject>(prefabs::asteroid3, sf::Vector2f{1100, 1100}, sf::Vector2f{1.f, -1.f});
        auto asteroid2 = std::make_shared<rendering::CollisionObject>(prefabs::asteroidBig2, sf::Vector2f{1400, 1400}, sf::Vector2f{1.f, 1.f});

        auto wolf = std::make_shared<ships::AiShip>(prefabs::wolf, sf::Vector2f{1800, 1200});
        auto lasher = std::make_shared<ships::AiShip>(prefabs::lasher, sf::Vector2f{1200, 1800});

        auto player = std::make_shared<ships::PlayerShip>(prefabs::scarab, sf::Vector2f{1250, 1250});

        drawables = {background, asteroid1, asteroid2, player, wolf, lasher};
        frameUpdateables = {asteroid1, asteroid2, player, wolf, lasher};
        collidables = {asteroid1, asteroid2, player, wolf, lasher};
        shooters = {player, wolf, lasher};
        aiShips = {wolf, lasher};
        hostileShips = {wolf, lasher};
        playerShips = {player};

        controledObject = player;

        for (auto &object : collidables)
            collisionModel.add(object);

        // populateArenaWithAsteroids(x, y);
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
    }

    void Arena::cleanupDeadObjects()
    {
        auto isDead = [](const auto &obj)
        {
            auto deadCheckable = std::dynamic_pointer_cast<DeadCheckable>(obj);
            return deadCheckable && (not deadCheckable->isAlive());
        };
        auto cleanupVector = [&isDead]<typename Vec>(Vec &vec)
        {
            vec.erase(std::remove_if(vec.begin(), vec.end(), isDead), vec.end());
        };
        cleanupVector(drawables);
        cleanupVector(collidables);
        cleanupVector(frameUpdateables);
        cleanupVector(shooters);
        cleanupVector(playerShips);
        cleanupVector(aiShips);

        // debugPrint();
    }

    void Arena::frameUpdate()
    {
        collisionModel.updateCollisions();

        for (auto &aiShip : aiShips)
            aiShip->determineTactic(hostileShips, playerShips, collidables, projectiles);

        for (auto &obj : frameUpdateables)
            obj->frameUpdate();

        for (auto &obj : shooters)
        {
            auto proj = obj->shoot();

            if (proj != nullptr)
            {
                collisionModel.add(proj);
                frameUpdateables.push_back(proj);
                drawables.push_back(proj);
                projectiles.push_back(proj);
            }
        }
        cleanupDeadObjects();

        sf::View v = window.getView();
        v.setCenter(controledObject->getSprite().getPosition());
        window.setView(v);
    }

    void Arena::draw()
    {
        // todo dont draw objects outside view
        for (auto &obj : drawables)
            window.draw(*obj);
    }

    void Arena::render()
    {

        window.clear(sf::Color::White);

        frameUpdate();
        draw();

        window.display();
    }
    Arena::~Arena()
    {
    }

    void Arena::debugPrint()
    {
        printf("drawables %zd, collidables %zd, frameUpd %zd, shooters %zd\n", drawables.size(), collidables.size(), frameUpdateables.size(), shooters.size());
        printf("\n----Arena----\n");
        for (auto &obj : drawables)
        {
            auto proj = std::dynamic_pointer_cast<ships::Projectile>(obj);
            std::string s = "";
            if (proj)
                s = proj->getId();

            auto collid = std::dynamic_pointer_cast<rendering::CollisionObject>(obj);
            if (collid)
                s = collid->getId();
            if (s != "")
                printf("[%s]\n", s.c_str());
        }
        std::cout << std::endl;
    }
} // namespace levels