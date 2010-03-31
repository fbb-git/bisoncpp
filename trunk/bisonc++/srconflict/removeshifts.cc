#include "srconflict.ih"

size_t SRConflict::removeShifts(Next::Vector &nextVector)
{
    for_each(d_rmShift.begin(), d_rmShift.end(),
        FnWrap::unary(Next::removeShift, nextVector));

    return d_rmShift.size();
}
