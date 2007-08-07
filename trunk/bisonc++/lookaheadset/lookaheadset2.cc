#include "lookaheadset.ih"

LookaheadSet::LookaheadSet(FirstSet const &firstSet)
:
    FirstSet(firstSet),
    d_EOF(e_withoutEOF)
{}
