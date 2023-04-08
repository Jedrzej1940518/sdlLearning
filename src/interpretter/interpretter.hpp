#pragma once

#include "../rendering/collisionObject.hpp"

namespace interpretter
{

    struct Process
    {
        };

    class Interpretter
    {
        rendering::CollisionObject *ship;

        bool rotation(const string &s);

    public:
        Interpretter() : ship{nullptr} {}
        void setControledObject(rendering::CollisionObject *controlledObject) { ship = controlledObject; }
        void handleCommand(const string &s);
    };
}