#include "semsizet.ih"

SemBase *SemSizeT::v_clone() const
{
    return new SemSizeT(*this);
}

size_t SemSizeT::v_size() const
{
    return d_size;
}
