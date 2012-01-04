#include "srconflict.ih"

size_t SRConflict::removeShifts(Next::Vector &nextVector)
{
    size_t nRemoved = 0;

    for (auto &rmShift: d_rmShift) 
        Next::removeShift(rmShift, nextVector, &nRemoved);

    return nRemoved;
}
