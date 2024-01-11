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
        "../data/graphics/asteroids/asteroid_big02.png", "asteroid1", {2, 3, 0, 1000}, 120};
    const inline Prefab asteroid2{"../data/graphics/asteroids/asteroid2.png", "asteroid2", {5, 7, 0, 200}, 20};
    const inline Prefab asteroid3{
        "../data/graphics/asteroids/asteroid3.png", "asteroid3", {5, 7, 0, 200}, 30};
    const inline Prefab scarab{
        "../data/graphics/ships/scarab.png", "scarab", {3, 5, 0.2, 500}, 300};

    const inline Prefab lasher{
        "../data/graphics/ships/lasher_ff.png", "lasher", {1.2, 4.5, 0.25, 500}, 50};
    const inline Prefab hammerhead{
        "../data/graphics/ships/hammerhead_dd.png", "hammerhead", {0.6, 3, 0.075, 800}, 150};
    const inline Prefab wolf{
        "../data/graphics/ships/wolf_ff.png", "wolf", {3.5, 6.5, 0.4, 250}, 40};

    const inline ProjectilePrefab lasherShell{{"../data/graphics/projectiles/shell_small_green.png", "shell", {0, 12, 1, 0}, 0}, 50, 5, 30, 6};
    const inline ProjectilePrefab hammerheadShell{{"../data/graphics/projectiles/bomblet2.png", "bomblet2", {0, 14, 1, 0}, 0}, 60, 8, 50, 3};
    const inline ProjectilePrefab scarabShell{{"../data/graphics/projectiles/rift_torpedo.png", "rift_torpedo", {0, 14, 1, 0}, 0}, 50, 10, 30, 3};
    const inline ProjectilePrefab torpedo{{"../data/graphics/projectiles/missile_torpedo_compact.png", "torpedo", {0, 10, 1, 0}, 0}, 60, 50, 300, 0};
}