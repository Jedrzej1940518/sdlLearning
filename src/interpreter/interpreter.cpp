#include "interpreter.hpp"
#include "line.hpp"
#include <regex>

namespace interpreter
{
    void Interpreter::handleCommand(const Line &line)
    {
        const auto &words = line.getWords();
        const string &command = words[0].getWord();

        auto &body = ship->getBody();

        if (command == "engage")
        {
            body.accelerate();
        }
        else if (command == "disengage")
        {
            body.deaccelerate();
        }
        else if (command == "stop")
        {
            body.deaccelerate();
            auto rotationNeeded = (getVectorRotation(body.getSpeed()) + 180.) - body.getRotation();
            body.rotate(rotationNeeded);
        }
        else if (command == "rotate")
        {
            if (words.size() < 2)
                return;

            double rotationNeeded = 0.0;

            try
            {
                const string &argument = words[1].getWord();
                rotationNeeded = stod(argument);
            }
            catch (const std::invalid_argument &ia)
            {
                std::cerr << "Invalid argument: " << ia.what() << '\n';
                return;
            }
            body.rotate(rotationNeeded);
        }
    }
}