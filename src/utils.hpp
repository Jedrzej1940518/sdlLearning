#pragma once

// #include "physics/physics.hpp"

#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <utility>
#include <memory>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "timer.hpp"

#ifndef M_PI
#define M_PI 3.14159265359f
#endif

namespace globals
{
	static inline sf::Color GREY{200, 200, 200, 200};
	extern sf::RenderWindow *WINDOW;
	extern Timer *TIMER;
}

namespace constants
{
	static inline constexpr float COLLISION_DAMAGE_FACTOR = 0.0f; // todo hehe
	static inline constexpr float COLLISION_BOUNCE = 0.1f;
	static inline constexpr float CARTESIAN_TO_SFML_ANGLE = 90.f;
	static inline constexpr float BASE_SAFE_DIST = 75.f;
}

namespace config
{
	inline static constexpr bool debugTactic{false};
	inline static constexpr bool debugObject{false};
	inline static unsigned constexpr int SCREEN_HEIGHT = 800;
	inline static unsigned constexpr int SCREEN_WIDTH = 1024;
	inline static unsigned constexpr int FRAME_RATE = 1024;

	inline static constexpr int ARENA_MAX_X = 750;
	inline static constexpr int ARENA_MAX_Y = 750;
	inline static constexpr float SHIP_LOST_REWARD = 10.f;
	inline static constexpr float REWARD_DENOMINATOR = 10.f;

	inline static constexpr int RED_TEAM = 0;
	inline static constexpr int BLUE_TEAM = 1;

	inline static constexpr float VIDEO_ZOOM_FACTOR = 1.6f;
	inline static constexpr float PREFAB_MULTIPLIER = 1.f;
	inline static constexpr int VIDEO_FRAME_RATE = 60 / PREFAB_MULTIPLIER;

	inline static constexpr bool SHOULD_TIME = true;
}

const char *findLastOccurrence(const char *str, const char *substr);

#define LOG(fmt, ...)                                                        \
	do                                                                       \
	{                                                                        \
		const char *relativePath = findLastOccurrence(__FILE__, "\\src\\");  \
		if (relativePath != nullptr)                                         \
		{                                                                    \
			printf("%s [%d] " fmt, relativePath + 5, __LINE__, __VA_ARGS__); \
		}                                                                    \
		else                                                                 \
		{                                                                    \
			printf("%s [%d] " fmt, __FILE__, __LINE__, __VA_ARGS__);         \
		}                                                                    \
		printf("\n");                                                        \
	} while (0)

namespace sf
{
	class Sprite;
	class CircleShape;
	class RectangleShape;
}

void initRendering();
void initTimer();

std::string boolToString(bool b);
std::string getDataPath(std::string dataPath);

std::pair<std::shared_ptr<sf::ConvexShape>, std::shared_ptr<sf::ConvexShape>> getVectorShapes(const sf::Vector2f &vector, const sf::Vector2f &center, sf::Color color, float multiplier = 15.f);
std::shared_ptr<sf::CircleShape> makeCircle(const sf::Vector2f &origin, float radius, sf::Color color);
std::shared_ptr<sf::RectangleShape> makeRectangle(const sf::Vector2f &size, sf::Color color);

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