#include "block.ih"

bool Block::close()
{
    *this += "}";
    return --d_count == 0;
}
