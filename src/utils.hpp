#pragma once

// #include "physics/physics.hpp"

#include <iostream>
#include <array>
#include <vector>
#include <random>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#ifndef M_PI
#define M_PI 3.14159265359f
#endif

namespace globals
{
    static inline sf::Color GREY{200, 200, 200, 200};
}

namespace constants
{
    static inline constexpr float COLLISION_DAMAGE_FACTOR = 2.0f;
    static inline constexpr float COLLISION_BOUNCE = 0.1f;
    static inline constexpr float CARTESIAN_TO_SFML_ANGLE = 90.f;
}

#define LOG(fmt, ...) \
    (printf("%s [%d] " fmt "\n", __FILE__, __LINE__, __VA_ARGS__));

// resolution
extern const unsigned int SCREEN_HEIGHT;
extern const unsigned int SCREEN_WIDTH;
extern const unsigned int FRAME_RATE;

namespace sf
{
    class Sprite;
}

std::string boolToString(bool b);
std::string getDataPath(std::string dataPath);

std::vector<sf::ConvexShape> getVectorShapes(const sf::Vector2f &vector, const sf::Vector2f &center, sf::Color color);
float getSpriteRadius(const sf::Sprite &sprite);

template <typename T>
T getRandomNumber(T from, T to)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>)
    {
        std::uniform_int_distribution<T> distribution(from, to);
        return distribution(gen);
    }
    else if constexpr (std::is_floating_point_v<T>)
    {
        std::uniform_real_distribution<T> distribution(from, to);
        return distribution(gen);
    }
}

// THIS IS DONE BY COPY ASSIGNMENT
template <typename T>
void removeVectorElement(std::vector<T> &vec, int indx)
{
    auto lastIndex = vec.size() - 1;
    if (indx != lastIndex)
        std::swap(vec[lastIndex], vec[indx]);
    vec.pop_back();
}