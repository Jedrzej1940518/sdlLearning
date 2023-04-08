#include "line.hpp"

namespace interpretter
{
    void Line::push_back(char c)
    {
        if (c == ' ')
        {
            words.push_back();
        }
        else
            words.back().push_back(c);
    }
    void Line::pop()
    {
        if (words.back().empty() and words.size() > 1) // always need one word in line
            words.pop();
        else
            words.back().pop();
    }
}