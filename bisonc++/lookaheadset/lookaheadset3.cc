#include "lookaheadset.ih"

LookaheadSet::LookaheadSet(LookaheadSet const &other)
:
    FirstSet(other),
    d_EOF(other.d_EOF)
{}
