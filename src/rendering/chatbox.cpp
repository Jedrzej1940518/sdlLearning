
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

        SDL_Rect dstRect = {dstrect.x + 20, dstrect.y + dstrect.h - textH * (i), textW, textH};

        SDL_FreeSurface(textSurface);
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_DestroyTexture(texture);
    }

    void Chatbox::renderText()
    {
        renderLine(start + current, 1);
        for (int i = 0; i < static_cast<int>(lines.size()); ++i)
        {
            const auto &line = lines.getElemReverse();

            if (line.empty())
                continue;

            renderLine(line, i + 2);
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

        for (size_t i = 0; i < instructions.size(); ++i)
        {
            string ins = instructions.getElem();
            if ((s + ins).size() > maxLineLenght)
            {
                lines.addElem(s);
                s = "";
            }
            s += ins + " ";
        }
        lines.addElem(s);
    }

    Carousel<string, Chatbox::maxInstructions> Chatbox::matchInstructions(const string &beggining)
    {
        const string instructionList[]{"rotate", "engage", "disengage", "stop"};
        Carousel<string, maxInstructions> c;

        regex pattern{"^" + beggining};

        for (const auto &s : instructionList)
        {
            if (std::regex_search(s, pattern))
                c.addElem(s);
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
            if (current.size() >= maxLineLenght)
                return;

            current += event.text.text;
            handleCompositionChange();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
        {
            interpretter.handleCommand(current);
            lines.addElem(start + current);
            current = "";
            handleCompositionChange();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
        {
            if (current.empty())
                return;

            current.pop_back();
            handleCompositionChange();
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_TAB)
        {
            if (current.empty())
                return;

            if (not listed)
            {
                instructions = matchInstructions(current);
                instructions.addElem(current);

                if (instructions.size() > 2)
                    listAllInstructions();
                else
                    current = instructions.getElem();
            }
            if (listed or instructions.size() == 2)
            {
                if (instructions.empty())
                    return;

                current = instructions.getElem();
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

        lines.addElem("Welcome Jedrzej");
        lines.addElem(" ");
    }

} // namespace rendering