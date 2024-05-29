#include "utils.hpp"
#include "physics/physics.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <unistd.h>
#include <limits.h>

namespace globals
{
	sf::RenderWindow *WINDOW{nullptr};
	Timer *TIMER{nullptr};
}

void initRendering()
{
	globals::WINDOW = new sf::RenderWindow(sf::VideoMode(config::SCREEN_WIDTH, config::SCREEN_HEIGHT), "My window");
	globals::WINDOW->setFramerateLimit(config::FRAME_RATE);
}

void initTimer()
{
	globals::TIMER = new Timer(config::SHOULD_TIME);
}

std::pair<std::shared_ptr<sf::ConvexShape>, std::shared_ptr<sf::ConvexShape>> getVectorShapes(const sf::Vector2f &vector, const sf::Vector2f &center, sf::Color color, float multiplier)
{
	std::shared_ptr<sf::ConvexShape> arrowBase = std::make_shared<sf::ConvexShape>();

	constexpr float w = 2.f;
	float l = physics::getVectorMagnitude(vector) * multiplier;
	float angle = physics::normalizeDegrees(physics::getVectorRotation(vector));

	arrowBase->setPointCount(4);
	arrowBase->setPoint(0, sf::Vector2f(0, 0));
	arrowBase->setPoint(1, sf::Vector2f(0, w));
	arrowBase->setPoint(2, sf::Vector2f(l, w));
	arrowBase->setPoint(3, sf::Vector2f(l, 0));
	arrowBase->setFillColor(color);
	arrowBase->setPosition(center);
	arrowBase->setOrigin({0, w / 2});
	arrowBase->setRotation(angle);

	std::shared_ptr<sf::ConvexShape> arrowPoint = std::make_shared<sf::ConvexShape>();
	arrowPoint->setPointCount(3);

	arrowPoint->setPoint(0, sf::Vector2f(l, -w));
	arrowPoint->setPoint(1, sf::Vector2f(l, w * 2));
	arrowPoint->setPoint(2, sf::Vector2f(l + w * 2, w / 2));
	arrowPoint->setFillColor(color);
	arrowPoint->setPosition(center);
	arrowPoint->setOrigin({0, w / 2});
	arrowPoint->setRotation(angle);

	return std::make_pair(std::move(arrowBase), std::move(arrowPoint));
}

std::shared_ptr<sf::CircleShape> makeCircle(const sf::Vector2f &origin, float radius, sf::Color color)
{
	auto p = std::make_shared<sf::CircleShape>(radius);
	p->setOrigin({radius, radius});
	p->setPosition(origin);
	p->setOutlineColor(color);
	p->setFillColor(sf::Color::Transparent);
	p->setOutlineThickness(3);
	return p;
}
std::shared_ptr<sf::RectangleShape> makeRectangle(const sf::Vector2f &size, sf::Color color)
{
	// Create a shared pointer to a new sf::RectangleShape
	std::shared_ptr<sf::RectangleShape> rectangle = std::make_shared<sf::RectangleShape>(size);

	// Set the fill color
	rectangle->setFillColor(sf::Color::Transparent);
	rectangle->setOutlineColor(color);
	rectangle->setOutlineThickness(3);

	return rectangle;
}

float getSpriteRadius(const sf::Sprite &sprite)
{
	auto rect = sprite.getTextureRect();
	return std::max(rect.width / 2.f, rect.height / 2.f);
}

const char *findLastOccurrence(const char *str, const char *substr)
{

	const char *last = nullptr;

	// while ((str = strstr(str, substr)) != nullptr) {
	// 	last = str;
	// 	str++;
	// }
	return last;
}

std::string getDataPath(std::string dataPath)
{
	char buffer[PATH_MAX];
	readlink("/proc/self/exe", buffer, PATH_MAX);

	std::string executablePath(buffer);
	std::string executableDirectory = executablePath.substr(0, executablePath.find_last_of("/"));

	return executableDirectory + "/data/" + dataPath;
}

std::string boolToString(bool b)
{
	return b ? "true" : "false";
}
