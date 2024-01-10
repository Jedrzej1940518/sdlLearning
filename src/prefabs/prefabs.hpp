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

    struct ProjectilePrefab : public Prefab
    {
        ProjectilePrefab(Prefab prefab, int lifetime, int dmg, int reload, int scatterAngle) : Prefab{prefab}, lifetime{lifetime}, dmg{dmg}, reload{reload}, scatterAngle{scatterAngle} {}
        int lifetime;
        int dmg;
        int reload;
        int scatterAngle;
    };

    const inline Prefab asteroidBig2{
        "../data/graphics/asteroids/asteroid_big02.png", "asteroid1", {2, 3, 0, 1000}, 20};
    const inline Prefab asteroid2{"../data/graphics/asteroids/asteroid2.png", "asteroid2", {5, 7, 0, 300}, 20};
    const inline Prefab asteroid3{
        "../data/graphics/asteroids/asteroid3.png", "asteroid3", {5, 7, 0, 300}, 20};
    const inline Prefab scarab{
        "../data/graphics/ships/scarab.png", "scarab", {3, 5, 0.2, 500}, 100};

    const inline Prefab lasher{
        "../data/graphics/ships/lasher_ff.png", "lasher", {1.2, 3.5, 0.2, 500}, 50};

    const inline ProjectilePrefab lasherShell{{"../data/graphics/projectiles/shell_small_green.png", "shell", {0, 20, 1, 0}, 0}, 100, 2, 15, 0};
    const inline ProjectilePrefab hammerheadShell{{"../data/graphics/projectiles/bomblet2.png", "bomblet2", {0, 9, 1, 0}, 0}, 50, 8, 15, 5};
    const inline ProjectilePrefab scarabShell{{"../data/graphics/projectiles/rift_torpedo.png", "rift_torpedo", {0, 14, 1, 0}, 0}, 50, 10, 30, 3};
    const inline ProjectilePrefab torpedo{{"../data/graphics/projectiles/missle_torpedo_compact.png", "torpedo", {0, 6, 1, 0}, 0}, 50, 50, 300, 1};
}