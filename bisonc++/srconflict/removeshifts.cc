#include "srconflict.ih"

size_t SRConflict::removeShifts(Next::Vector &nextVector)
{
    size_t nRemoved = 0;

    for_each(
        d_rmShift.begin(), d_rmShift.end(),
        [&](RmShift const &rmShift)
        {
            Next::removeShift(rmShift, nextVector, &nRemoved);
        }
    );

    return nRemoved;
}
