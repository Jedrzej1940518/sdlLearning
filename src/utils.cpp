#include "utils.hpp"
#include "physics/physics.hpp"

#include <Windows.h>

const unsigned int SCREEN_HEIGHT = 800;
const unsigned int SCREEN_WIDTH = 1000;
const unsigned int FRAME_RATE = 120;

std::vector<sf::ConvexShape> getVectorShapes(const sf::Vector2f &vector, const sf::Vector2f &center, sf::Color color)
{
    sf::ConvexShape arrowBase;

    constexpr float w = 10.f;
    float l = physics::vectorLenght(vector) * 15.f;
    float angle = physics::normalizeDegrees(physics::getVectorRotation(vector));

    arrowBase.setPointCount(4);
    arrowBase.setPoint(0, sf::Vector2f(0, 0));
    arrowBase.setPoint(1, sf::Vector2f(0, w));
    arrowBase.setPoint(2, sf::Vector2f(l, w));
    arrowBase.setPoint(3, sf::Vector2f(l, 0));
    arrowBase.setFillColor(color);
    arrowBase.setPosition(center);
    arrowBase.setOrigin({0, w / 2});
    arrowBase.setRotation(angle);

    std::vector<sf::ConvexShape> arrowShapes;
    arrowShapes.push_back(arrowBase);

    sf::ConvexShape arrowPoint;
    arrowPoint.setPointCount(3);

    arrowPoint.setPoint(0, sf::Vector2f(l, -w));
    arrowPoint.setPoint(1, sf::Vector2f(l, w * 2));
    arrowPoint.setPoint(2, sf::Vector2f(l + w * 2, w / 2));
    arrowPoint.setFillColor(color);
    arrowPoint.setPosition(center);
    arrowPoint.setOrigin({0, w / 2});
    arrowPoint.setRotation(angle);

    arrowShapes.push_back(arrowPoint);

    return arrowShapes;
}

std::string getDataPath(std::string dataPath)
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);

    std::string executablePath(buffer);
    std::string executableDirectory = executablePath.substr(0, executablePath.find_last_of("\\/"));
    return executableDirectory + "\\" + dataPath;
}

std::string boolToString(bool b)
{
    return b ? "true" : "false";
}
