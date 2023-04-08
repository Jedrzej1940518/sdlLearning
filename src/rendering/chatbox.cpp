
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

    void Chatbox::renderLine(const string &s, int i)
    {
        SDL_Surface *textSurface = TTF_RenderText_Blended(font, s.c_str(), textColor);

        if (!textSurface)
            cerr << "Error loading font for chatbox!" << endl;

        auto textW = textSurface->w;
        auto textH = textSurface->h;
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect dstRect = {dstrect.x + 20, dstrect.y + textH * (i), textW, textH};

        SDL_FreeSurface(textSurface);
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_DestroyTexture(texture);
    }

    void Chatbox::renderText()
    {
        int i = 0;
        for (const auto &line : lines)
        {
            ++i;
            if (line.empty()) // todo this needed?
                continue;

            renderLine(line, i);
        }
    }

    void Chatbox::handleCompositionChange()
    {
        listed = false;

        instructions.clear();
    }

    void Chatbox::listAllInstructions()
    {
        string s = "";

        for (const auto &ins : instructions)
        {
            if ((s + ins).size() > maxLineLenght)
            {
                lines.push_back(s);
                s = "";
            }
            s += ins + " ";
        }
        lines.push_back(s);
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

        renderText();
    }

    void Chatbox::handleEvent(SDL_Event &event)
    {
        if (event.type == SDL_TEXTINPUT)
        {
            if (lines.back().size() >= maxLineLenght)
                return;

            lines.back() += event.text.text;
            handleCompositionChange();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
        {
            interpretter.handleCommand(lines.back());
            lines.push_back(start + lines.back());
            lines.back() = "";
            handleCompositionChange();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
        {
            if (lines.back().empty())
                return;

            lines.back().pop_back();
            handleCompositionChange();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_TAB)
        {
            if (lines.back().empty())
                return;

            if (not listed)
            {
                instructions = matchInstructions(lines.back());
                instructions.push_back(lines.back());

                if (instructions.size() > 2)
                    listAllInstructions();
                else
                    lines.back() = instructions.back();
            }
            if (listed or instructions.size() == 2)
            {
                if (instructions.empty())
                    return;

                lines.back() = instructions.back();
            }
            listed = true;
        }
    }
    void Chatbox::setControledObject(rendering::CollisionObject *ship)
    {
        interpretter.setControledObject(ship);
    }

    void Chatbox::initTextSize()
    {
        int desiredTextH = linesRect.h / (maxLines + 1);
        textH = desiredTextH + 1;
        int currentH = textH + 1;

        do
        {
            --textH;
            font = TTF_OpenFont("../data/graphics/fonts/TiltNeon-Regular.ttf", textH);
            TTF_SizeText(font, "s", nullptr, &currentH);

            if (currentH < 0 or textH < 0)
            {
                cerr << "Cant find right font size!\n";
                exit(1);
            }

        } while (currentH > desiredTextH);
    }

    Chatbox::Chatbox(SDL_Renderer *renderer, SDL_Rect dstrect)
        : renderer{renderer}, font{font}, dstrect{dstrect}
    {
        constexpr int xMargin = 10;
        constexpr int yMargin = 10;
        linesRect = {dstrect.x + xMargin, dstrect.y + yMargin, dstrect.w - xMargin, dstrect.h - yMargin};

        initTextSize();

        lines.push_back("Welcome Jedrzej");
        lines.push_back(" 1");
        lines.push_back(" 2");
        lines.push_back(" 3");
    }

} // namespace rendering