#pragma once

class DeadCheckable
{
protected:
    bool alive{true};

public:
    bool isAlive() { return alive; }
};