#include "block.hh"

bool Block::close()
{
    *this += "}";
    return --d_count == 0;
}
