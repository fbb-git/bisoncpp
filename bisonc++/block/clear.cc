#include "block.ih"

void Block::clear()
{
    erase();
    d_skip.clear();
    d_count = 0;
}
