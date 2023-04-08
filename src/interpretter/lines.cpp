#include "lines.hpp"

namespace interpretter
{
    void Lines::initTextSize()
    {
        int desiredTextH = dstrect.h / (maxLines + 1);
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

    void Lines::newLine()
    {
        lines.push_back();
    }

    void Lines::push_back(char c)
    {
        lines.back().push_back(c);
    }
    void Lines::pop()
    {
        lines.back().pop();
    }
    void Lines::render()
    {
        physics::Vector2d position{dstrect.x, dstrect.y};

        for (auto &line : lines)
        {
            for (auto &word : line.getWords())
            {
                auto &&[w, h] = word.render(font, renderer, position);
                position.x += w;
            }
            position.y += h;
        }
    }
}