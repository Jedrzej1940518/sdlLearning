#pragma once

#include "../physics/hardware.hpp"
#include <string>

namespace prefabs
{
    using physics::Hardware;

    struct Prefab
    {
        std::string texturePath;
        std::string id;
        Hardware hardware;
    };

    inline Prefab asteroidBig2{
        "../data/graphics/asteroids/asteroid_big02.png", "asteroid1", {2, 3, 0, 1000}};
    inline Prefab asteroid2{"../data/graphics/asteroids/asteroid2.png", "asteroid2", {5, 7, 0, 300}};
    inline Prefab asteroid3{
        "../data/graphics/asteroids/asteroid3.png", "asteroid3", {5, 7, 0, 300}};
    inline Prefab scarab{
        "../data/graphics/ships/scarab.png", "scarab", {3, 5, 0.2, 500}};
}