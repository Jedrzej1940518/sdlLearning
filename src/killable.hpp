#pragma once

class Killable
{
protected:
    bool alive{true};

public:
    bool isAlive() { return alive; }
};