#include "lines.hpp"

namespace interpreter
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
    void Lines::pop_back()
    {
        lines.back().pop_back();
    }
    void Lines::render()
    {
        int x = dstrect.x;
        int y = dstrect.y;
        int height;
        for (auto &line : lines)
        {
            for (const auto &word : line.getWords())
            {
                auto &&[w, h] = word.render(font, renderer, x, y);
                x += w;
                height = h;
            }
            x = dstrect.x;
            y += height;
        }
    }
}