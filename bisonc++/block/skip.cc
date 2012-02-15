#include "block.ih"

bool Block::skip(string const &text)
{
    size_t begin = length();

    if (!operator()(text))
        return false;

    d_skip.push_back({begin, length()});
    return true;
}
