#include "semblock.ih"

SemBase *SemBlock::v_clone() const
{
    return new SemBlock(*this);
}

Block const &SemBlock::v_block() const
{
    return d_block;
}
