#include "state.ih"

State::State(size_t/*unsigned*/ idx)
:
    d_type(NORMAL),
    d_idx(idx),
    d_construct(true),
    d_nTransitions(0),
    d_nTerminalTransitions(0),
    d_nRRConflicts(0),
    d_defaultReduction(0)
{}
