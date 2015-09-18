#include "block.hh"

bool Block::operator()(string const &text)
{
    if (d_count == 0)
        return false;

    *this += text;
    return true;
}
