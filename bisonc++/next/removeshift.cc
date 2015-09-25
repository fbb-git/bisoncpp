#include "next.ih"

void Next::removeShift(RmShift const &rmShift, Vector &nextVector, 
                        size_t *nRemoved)
{
    Next &next = nextVector[rmShift.idx()];

    if (next.d_symbol)      // removeShift may be called multiple times.
    {                       // This prevents d_removed from being overwritten
        next.d_removed = next.d_symbol;
        next.d_forced = rmShift.forced();
        next.d_symbol = 0;
        ++*nRemoved;
    }
}

