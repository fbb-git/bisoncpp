#include "block.ih"

void Block::clear()
{
    erase();
    d_atDollar.clear();
    d_count = 0;
}
