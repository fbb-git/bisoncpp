#ifndef INCLUDED_SEMBLOCK_
#define INCLUDED_SEMBLOCK_

#include "../sembase/sembase.h"

#include "../block/block.h"

class SemBlock: public SemBase
{
    mutable Block d_block;

    public:
        SemBlock(Block const &block);
        operator Block &() const;
};

inline SemBlock::SemBlock(Block const &block)
:
    SemBase(Tag::BLOCK),
    d_block(block)
{}

inline SemBlock::operator Block &() const
{
    return d_block;
}

template <>
struct Type<SemEnum::Tag::BLOCK>
{
    typedef SemBlock const &conversionType;
    typedef Block &semType;
};
        
#endif



