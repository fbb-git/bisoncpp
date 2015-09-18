#include "rrdata.hh"

RRData::RRData(LookaheadSet laSet)
:
    d_laSet(laSet),
    d_forced(false),
    d_kept(~0)
{}

