#ifndef INCLUDED_SEMSIZET_
#define INCLUDED_SEMSIZET_

#include "../sembase/sembase.h"

class SemSizeT: public SemBase
{
    size_t d_size;

    public:
        SemSizeT(size_t size = 0);
        operator size_t() const;
};

inline SemSizeT::SemSizeT(size_t size)
:
    SemBase(Tag::SIZE_T),
    d_size(size)
{}
        
inline SemSizeT::operator size_t() const
{
    return d_size;
}

template <>
struct Type<SemEnum::Tag::SIZE_T>
{
    typedef SemSizeT const &conversionType;
    typedef size_t semType;
};

#endif
