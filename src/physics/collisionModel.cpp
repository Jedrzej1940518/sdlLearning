#include "collisionModel.hpp"

namespace physics
{
    template <typename Vec>
    void debugPrint(Vec &v, std::string s)
    {
        printf("----%s----\n", s.c_str());
        for (auto &obj : v)
            printf("%s\n", obj->getId().c_str());
        std::cout << std::endl;
    }
    void CollisionModel::updateCollisions()
    {
        // projectiles
        // collidables
        auto cmp = []<typename Object>(const Object &a, const Object &b)
        { return a->getCenter().x < b->getCenter().x; };

        auto isDead = [](const auto &obj)
        { return not obj->isAlive(); };

        auto cleanupVector = [&isDead]<typename Vec>(Vec &vec)
        { vec.erase(std::remove_if(vec.begin(), vec.end(), isDead), vec.end()); };

        cleanupVector(collidables);
        cleanupVector(projectiles);

        for (auto &proj : projectiles)
        {
            for (auto &collidable : collidables)
            {
                // if we hit something, we stop checking rest of collidables
                if (not proj->isAlive())
                    break;

                if (collisionHappening(proj->getCollisionCircle(), collidable->getCollisionCircle()))
                    proj->handleCollision(*collidable);
            }
        }
        for (auto &a : collidables)
        {
            for (auto &b : collidables)
            {
                if (a != b && collisionHappening(a->getCollisionCircle(), b->getCollisionCircle()))
                    a->handleCollision(*b);
            }
        }
        // debugPrint(collidables, "collidables");
        // debugPrint(projectiles, "projectiles");
        // std::sort(collidables.begin(), collidables.end(), cmp);
        // std::sort(projectiles.begin(), projectiles.end(), cmp);
    }
} // namespace physics