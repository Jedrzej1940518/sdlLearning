#include "line.hpp"

namespace interpreter
{
    Line::Line() : words{}
    {
        words.push_back({}); // starts with one empty word
    }

    void Line::push_back(char c)
    {
        if (c == ' ')
        {
            if (words.back().size() > 0) // only add new words if previous one was not empty
                words.push_back({});
        }
        else
            words.back().push_back(c);
    }
    void Line::pop_back()
    {
        if (words.back().empty() and words.size() > 1) // always need one word in line
            words.pop_back();
        else
            words.back().pop_back();
    }
    uint Line::size() const
    {
        int size = 0;
        for (const auto &word : words)
            size += word.size() + 1;

        --size;
        return static_cast<uint>(size);
    }
}