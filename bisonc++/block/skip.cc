#include "block.ih"

#include <iostream>

bool Block::skip(char const *text)
{
    size_t begin = length();

    if (!operator()(text))
        return false;

    d_skip.push_back({begin, length()});
    return true;
}
