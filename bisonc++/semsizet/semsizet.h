#ifndef INCLUDED_SEMSIZET_
#define INCLUDED_SEMSIZET_

#include "../sembase/sembase.h"

class SemSizeT: public SemBase
{
    size_t d_size;

    public:
        SemSizeT(size_t size = 0);
};

inline SemSizeT::SemSizeT(size_t size)
:
    SemBase(Type::SIZE_T),
    d_size(size)
{}
        
#endif
