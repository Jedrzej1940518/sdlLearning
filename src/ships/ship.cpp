
#include "ship.hpp"
// #include "soundManager.hpp"

namespace ships
{
    Ship::Ship(const prefabs::Prefab &prefab, sf::Vector2f position, sf::Vector2f velocity,
               float rotation) : CollisionObject{prefab, position, velocity, rotation}
    {
        spawnProjectile = false;
        for (int i = 0; i < 4; ++i)
        {
            inputDirections[i] = false;
        }
    }

    void Ship::handleEvents(const sf::Event &event)
    {
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            bool pressed = (event.type == sf::Event::KeyPressed);

            switch (event.key.code)
            {
            case sf::Keyboard::A:
                handleInput(physics::DIRECTION::left, pressed);
                break;
            case sf::Keyboard::D:
                handleInput(physics::DIRECTION::right, pressed);
                break;
            case sf::Keyboard::W:
                handleInput(physics::DIRECTION::up, pressed);
                break;
            case sf::Keyboard::S:
                handleInput(physics::DIRECTION::down, pressed);
                break;
            default:
                break;
            }
        }
    }

    void Ship::handleInput(physics::DIRECTION dir, bool pressed)
    {
        float angle = static_cast<float>(dir);
        int indx = static_cast<int>(angle / 90.);
        inputDirections[indx] = pressed;
    }

    void Ship::shoot()
    {
        // if (shellReload <= 0)
        // {
        //     spawnProjectile = true;
        //     soundsToPlay.insert(Sound::PLAYER_WEAPON);
        // }
    }

    // void Ship::rotateLeft()
    // {
    //     // body.rotate(-360);
    // }

    // void Ship::rotateRight()
    // {
    //     // body.rotate(360);
    // }
    // void Ship::stopRotateLeft()
    // {
    //     // body.rotate(0);
    // }

    // void Ship::stopRotateRight()
    // {
    //     // body.rotate(0);
    // }

    // void Ship::renderReload(SDL_Rect viewport)
    // {
    //     // ship rect
    //     SDL_Rect reloadRect{viewport.w / 2 - getWidth() / 2, viewport.h / 2 - getHeight() / 2, getWidth(), getHeight()};
    //     reloadRect.y += getHeight() + 10;
    //     reloadRect.h = 5;

    //     // yellow
    //     SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
    //     double reloadPercent = static_cast<double>(shellReload) / prefabs::scarabShell.reload;

    //     int reloadWidth = static_cast<int>(reloadRect.w * reloadPercent);

    //     SDL_Rect filledReload = {reloadRect};
    //     filledReload.w = reloadWidth;

    //     SDL_RenderFillRect(gRenderer, &filledReload);

    //     SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    //     SDL_RenderDrawRect(gRenderer, &reloadRect);
    // }
    // void Ship::renderObject(SDL_Rect viewport)
    // {
    //     CollisionObject::renderObject(viewport);
    //     renderReload(viewport);
    // }
    void Ship::frameUpdate()
    {
        CollisionObject::frameUpdate();
        bool accelerateOnce = false;

        for (int i = 0; i < 4; ++i)
            accelerateOnce |= inputDirections[i];

        if (accelerateOnce)
            body.accelerateOnce(physics::sumDirections(inputDirections));
    }
    // Projectile *Ship::frameUpdate(CollisionModel &collisionModel)
    // {
    //     CollisionObject::frameUpdate(collisionModel);
    //     bool accelerateOnce = false;

    //     for (int i = 0; i < 4; ++i)
    //     {
    //         accelerateOnce |= inputDirections[i];
    //     }

    //     if (accelerateOnce)
    //         body.accelerateOnce(physics::sumDirections(inputDirections));

    //     shellReload = std::max(shellReload - 1, 0);
    //     Projectile *projectile = nullptr;
    //     if (spawnProjectile)
    //     {
    //         projectile = Projectile::spawnProjectile(prefabs::scarabShell, *this);
    //         shellReload = prefabs::scarabShell.reload;
    //         spawnProjectile = false;
    //     }

    //     if (accelerateOnce || abs(body.getRotationLeft()) > 0)
    //         SoundManager::GetInstance().playUniqueSound(Sound::ENGINE);
    //     else
    //         SoundManager::GetInstance().pauseUniqueSound(Sound::ENGINE);

    //     return projectile;
    // }
}