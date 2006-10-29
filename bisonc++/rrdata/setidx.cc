#include "rrdata.ih"

void RRData::setIdx(Keep keep, size_t first, size_t second) 
{
    if (keep == KEEP_FIRST)
    {
        d_idx = second;
        d_kept = first;
    }
    else
    {
        d_idx =  first;
        d_kept = second;
    }

    d_forced = true;
}

