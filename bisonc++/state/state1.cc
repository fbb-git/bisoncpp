#include "state.ih"

State::State(unsigned idx)
:
    d_type(NORMAL),
    d_idx(idx),
    d_construct(true),
    d_nTransitions(0),
    d_nTerminalTransitions(0),
    d_defaultReduction(0)
{}
