#pragma once

#include "../rendering/collisionObject.hpp"

namespace interpreter
{
    class Line;
    class Interpreter
    {
        rendering::CollisionObject *ship;

    public:
        Interpreter() : ship{nullptr} {}
        void setControledObject(rendering::CollisionObject *controlledObject) { ship = controlledObject; }
        void handleCommand(const Line &line);
    };
}