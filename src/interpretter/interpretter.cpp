#include "interpretter.hpp"
#include <regex>

namespace interpretter
{

    void Interpretter::handleCommand(const string &s)
    {
        regex pattern("(rotate) ([0-9]+)");
        string str = "rotate 90";
        smatch match;

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
            body.rotate(-getVectorRotation(body.getSpeed()));
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