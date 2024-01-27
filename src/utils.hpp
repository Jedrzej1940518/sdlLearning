#pragma once

#include "mySdl.hpp"
#include "physics/physics.hpp"

#include <iostream>
#include <array>
#include <vector>
#include <random>

using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;

#define LOG(fmt, ...) \
    (printf("%s [%d] " fmt "\n", __FILE__, __LINE__, __VA_ARGS__));

// resolution
extern const unsigned int SCREEN_HEIGHT;
extern const unsigned int SCREEN_WIDTH;
extern const unsigned int FRAME_RATE;

inline SDL_Window *gWindow = nullptr;
inline SDL_Renderer *gRenderer = nullptr;
inline TTF_Font *gFont = nullptr;
inline TTF_Font *gBigFont = nullptr;

enum class LevelType
{
    MENU,
    ARENA,
    GAME_OVER,
    GAME_WON
};

void printRectangle(SDL_Rect rectangle);
void printPoint(SDL_Point point);

string boolToString(bool b);
string getDataPath(string dataPath);

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
    std::swap(vec[lastIndex], vec[indx]);
    vec.pop_back();
}