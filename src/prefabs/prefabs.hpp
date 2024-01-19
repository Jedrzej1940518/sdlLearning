#pragma once

#include "utils.hpp"

#include <string>

namespace prefabs
{
    struct Prefab
    {
        const std::string texturePath;
        const std::string id;
    };

    struct ObjectPrefab : Prefab
    {
        float maxVelocity;
        float mass;
        float maxRotationSpeed;
        float maxAcceleration;
    };

    struct CollidablePrefab : ObjectPrefab
    {
        int hp;
    };

    struct ProjectilePrefab : Prefab
    {
        int lifetime;
        int dmg;
        int reload;
        float maxVelocity;
        float scatterAngle;
    };

    struct ShipPrefab : CollidablePrefab
    {
        const ProjectilePrefab &weaponPrefab;
    };

    const inline Prefab background{getDataPath("graphics/backgrounds/background3.jpg"), "background3"};

    const inline CollidablePrefab asteroid2{getDataPath("graphics/asteroids/asteroid2.png"), "asteroid2", 4, 600, 4, 0.f, 60};
    const inline CollidablePrefab asteroid3{getDataPath("graphics/asteroids/asteroid3.png"), "asteroid3", 3, 1200, 3, 0.f, 120};
    const inline CollidablePrefab asteroidBig2{getDataPath("graphics/asteroids/asteroid_big02.png"), "asteroid1", 2.5, 2000, 2.5f, 0.f, 200};

    // const inline Prefab hammerhead{getDataPath(
    //                                    "data/graphics/ships/hammerhead_dd.png")
    //                                    .c_str(),
    //                                "hammerhead",
    //                                {0.6, 3, 0.075, 800},
    //                                150};

    // const inline ProjectilePrefab lasherShell{Prefab{getDataPath("graphics/projectiles/shell_small_green.png"), "shell", 5}, 50, 5, 30, 6.f};
    // const inline ProjectilePrefab hammerheadShell{Prefab{getDataPath("graphics/projectiles/bomblet2.png"), "big_shell", 8}, 60, 6, 50, 3.f};
    const inline ProjectilePrefab scarabShell{getDataPath("graphics/projectiles/rift_torpedo.png"), "scarab_shell", 30, 5, 10, 10, 3.f};
    // // const inline ProjectilePrefab torpedo{getDataPath("graphics/projectiles/missile_torpedo_compact.png"), "torpedo", 60, 50, 4, 300, 0};

    const inline ShipPrefab lasher{getDataPath("graphics/ships/lasher_ff.png"), "lasher", 4.5, 1200, 4.5, 0.45f, 300, scarabShell};
    const inline ShipPrefab wolf{getDataPath("graphics/ships/wolf_ff.png"), "wolf", 5.5, 600, 6, 0.7f, 300, scarabShell};
    const inline ShipPrefab scarab{getDataPath("graphics/ships/scarab.png"), "scarab", 5, 1000, 5, 0.5f, 300, scarabShell};
               
}