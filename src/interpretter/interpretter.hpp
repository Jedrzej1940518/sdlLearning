#pragma once

#include "../rendering/collisionObject.hpp"

namespace interpretter
{
    class Interpretter
    {
        rendering::CollisionObject *ship;

    public:
        Interpretter() : ship{nullptr} {}
        void setControledObject(rendering::CollisionObject *controlledObject) { ship = controlledObject; }
        void handleCommand(const string &s);
    };
}