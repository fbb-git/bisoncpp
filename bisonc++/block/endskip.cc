#include "block.ih"

bool Block::endSkip(char const *text)
{
    if (!operator()(text))
        return false;

    d_skip.back().second = d_source.length();
    return true;
}
