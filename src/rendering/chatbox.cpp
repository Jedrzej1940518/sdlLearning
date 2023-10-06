
#include "chatbox.hpp"
#include "../utils.hpp"
#include <iostream>
#include <regex>
#include <ranges>

namespace rendering
{
    Chatbox::~Chatbox()
    {
        TTF_CloseFont(font);
    }
    Chatbox::Chatbox(SDL_Renderer *renderer, SDL_Rect dstrect)
        : renderer{renderer}, font{font}, dstrect{dstrect}, lines{{dstrect.x + xLinesMargin, dstrect.y + yLinesMargin, dstrect.w - xLinesMargin, dstrect.h - yLinesMargin}, renderer}
    {
        string s("Welcome Jedrzej");
        for (auto c : s)
            lines.push_back(c);
        lines.newLine();
    }

    void Chatbox::handleCompositionChange()
    {
        listed = false;

        instructions.clear();
    }

    void Chatbox::listAllInstructions()
    {
        // string s = "";

        // for (const auto &ins : instructions)
        // {
        //     if ((s + ins).size() > maxLineLenght)
        //     {
        //         lines.push_back(s);
        //         s = "";
        //     }
        //     s += ins + " ";
        // }
        // lines.push_back(s);
    }

    boost::circular_buffer<string> Chatbox::matchInstructions(const string &beggining)
    {
        const string instructionList[]{"rotate", "engage", "disengage", "stop"};
        boost::circular_buffer<string> c{maxInstructions};

        regex pattern{"^" + beggining};

        for (const auto &s : instructionList)
        {
            if (std::regex_search(s, pattern))
                c.push_back(s);
        }
        return c;
    }

    void Chatbox::render()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &dstrect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &dstrect);

        lines.render();
    }

    void Chatbox::handleEvent(SDL_Event &event)
    {
        if (event.type == SDL_TEXTINPUT)
        {
            if (lines.back().size() >= maxLineLenght)
                return;

            char *c = event.text.text;
            while (*c)
            {
                lines.push_back(*c);
                ++c;
            }
            handleCompositionChange();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
        {
            interpreter.handleCommand(lines.back());
            lines.newLine();
            handleCompositionChange();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
        {
            lines.pop_back();
            handleCompositionChange();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_TAB)
        {
            // if (lines.back().empty())
            //     return;

            // if (not listed)
            // {
            //     instructions = matchInstructions(lines.back());
            //     instructions.push_back(lines.back());

            //     if (instructions.size() > 2)
            //         listAllInstructions();
            //     else
            //         lines.back() = instructions.back();
            // }
            // if (listed or instructions.size() == 2)
            // {
            //     if (instructions.empty())
            //         return;

            //     lines.back() = instructions.back();
            // }
            // listed = true;
        }
    }
    void Chatbox::setControledObject(rendering::CollisionObject *ship)
    {
        interpreter.setControledObject(ship);
    }

} // namespace rendering