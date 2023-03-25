#include "interpretter.hpp"
#include <regex>

namespace interpretter
{
    /*
        regex pattern("(rotate) ([0-9]+)");
    string str = "rotate 90";
    smatch match;

    if (regex_search(str, match, pattern)) {
        for (size_t i = 0; i < match.size(); ++i) {
            cout << "Matched group " << i << ": " << match[i] << endl;
        }
        */
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
        else if (s == "rotate")
        {
            body.rotate(90.f);
        }
    }
}