#include "semunion.ih"

SemUnion::~SemUnion()
{
    switch (d_index)
    {
        default:
        break;

        case STRING:
            d_str.~string();
        break;

        case BLOCK:
            d_block.~Block();
        break;
    }
}
