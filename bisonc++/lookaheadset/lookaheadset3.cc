#include "lookaheadset.hh"

LookaheadSet::LookaheadSet(LookaheadSet const &other)
:
    FirstSet(other),
    d_EOF(other.d_EOF)
{}
