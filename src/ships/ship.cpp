
#include "ship.hpp"

namespace ships
{
    Ship::Ship(const prefabs::Prefab &prefab, physics::Vector2d position, physics::Vector2d velocity,
               double rotation) : CollisionObject{prefab, position, velocity, rotation}
    {
        spawnProjectile = false;
        for (int i = 0; i < 4; ++i)
        {
            inputDirections[i] = false;
        }
    }

    void Ship::addInput(physics::DIRECTION dir)
    {
        double angle = static_cast<double>(dir);
        int indx = angle / 90.;
        inputDirections[indx] = true;
    }
    void Ship::removeInput(physics::DIRECTION dir)
    {
        double angle = static_cast<double>(dir);
        int indx = angle / 90.;
        inputDirections[indx] = false;
    }

    void Ship::shoot()
    {
        if (shellReload <= 0)
            spawnProjectile = true;
    }

    void Ship::rotateLeft()
    {
        body.rotate(-360);
    }

    void Ship::rotateRight()
    {
        body.rotate(360);
    }
    void Ship::stopRotateLeft()
    {
        body.rotate(0);
    }

    void Ship::stopRotateRight()
    {
        body.rotate(0);
    }

    void Ship::renderReload(SDL_Rect viewport)
    {

        // ship rect
        SDL_Rect reloadRect{viewport.w / 2 - getWidth() / 2, viewport.h / 2 - getHeight() / 2, getWidth(), getHeight()};
        reloadRect.y += getHeight() + 10;
        reloadRect.h = 5;

        // yellow
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
        float reloadPercent = static_cast<double>(shellReload) / prefabs::scarabShell.reload;

        int reloadWidth = static_cast<int>(reloadRect.w * reloadPercent);

        SDL_Rect filledReload = {reloadRect};
        filledReload.w = reloadWidth;

        SDL_RenderFillRect(gRenderer, &filledReload);

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(gRenderer, &reloadRect);
    }
    void Ship::renderObject(SDL_Rect viewport)
    {
        CollisionObject::renderObject(viewport);
        renderReload(viewport);
    }
    Projectile *Ship::frameUpdate(CollisionModel &collisionModel)
    {
        CollisionObject::frameUpdate(collisionModel);
        bool accelerateOnce = false;

        for (int i = 0; i < 4; ++i)
        {
            accelerateOnce |= inputDirections[i];
        }

        if (accelerateOnce)
            body.accelerateOnce(physics::sumDirections(inputDirections));

        shellReload = std::max(shellReload - 1, 0);
        Projectile *projectile = nullptr;
        if (spawnProjectile)
        {
            projectile = Projectile::spawnProjectile(prefabs::scarabShell, *this);
            shellReload = prefabs::scarabShell.reload;
            spawnProjectile = false;
        }

        return projectile;
    }
}