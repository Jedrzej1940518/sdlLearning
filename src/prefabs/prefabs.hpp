#pragma once

#include "../physics/hardware.hpp"
#include <string>

namespace prefabs
{
    using physics::Hardware;

    struct Prefab
    {
        const std::string texturePath;
        const std::string id;
        Hardware hardware;
        int hp;
    };

    inline Prefab asteroidBig2{
        "../data/graphics/asteroids/asteroid_big02.png", "asteroid1", {2, 3, 0, 1000}, 20};
    inline Prefab asteroid2{"../data/graphics/asteroids/asteroid2.png", "asteroid2", {5, 7, 0, 300}, 20};
    inline Prefab asteroid3{
        "../data/graphics/asteroids/asteroid3.png", "asteroid3", {5, 7, 0, 300}, 20};
    inline Prefab scarab{
        "../data/graphics/ships/scarab.png", "scarab", {3, 5, 0.2, 500}, 100};

    inline Prefab ememyScarab{
        "../data/graphics/ships/scarab.png", "enemyScarab", {2, 4, 0.2, 500}, 50};

    struct ProjectilePrefab : public Prefab
    {
        ProjectilePrefab(Prefab prefab, int lifetime, int dmg) : Prefab{prefab}, lifetime{lifetime}, dmg{dmg} {}
        int lifetime;
        int dmg;
    };

    inline ProjectilePrefab shell{{"../data/graphics/projectiles/shell_small_green.png", "shell", {0, 1, 1, 0}, 1}, 50, 10};
}