#include "interpretter.hpp"
#include <regex>

namespace interpretter
{

    void Interpretter::handleCommand(const string &s)
    {
        auto &body = ship->getBody();

        if (s == "engage")
        {
            body.accelerate();
        }
        else if (s == "disengage")
        {
            body.deaccelerate();
        }
        else if (s == "stop")
        {
            body.deaccelerate();
            auto rotationNeeded = (getVectorRotation(body.getSpeed()) + 180.) - body.getRotation();
            body.rotate(rotationNeeded);
        }
        else if (rotation(s))
        {
        }
    }

    bool Interpretter::rotation(const string &s)
    {
        regex pattern("(rotate) *(-?[0-9]+)");
        smatch match;

        if (regex_search(s, match, pattern))
        {
            double degrees = 0;
            try
            {
                degrees = stod(match[2]);
            }
            catch (...)
            {
                degrees = 0;
            }

            ship->getBody().rotate(degrees);
            return true;
        }
        else
            return false;
    }
}