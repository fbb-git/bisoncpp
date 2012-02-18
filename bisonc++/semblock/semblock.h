#ifndef INCLUDED_SEMBLOCK_
#define INCLUDED_SEMBLOCK_

#include "../sembase/sembase.h"

#include "../block/block.h"

class SemBlock: public SemBase
{
    Block d_block;

    public:
        SemBlock(Block const &block = Block());
};

inline SemBlock::SemBlock(Block const &block)
:
    SemBase(Type::BLOCK),
    d_block(block)
{}
        
#endif
