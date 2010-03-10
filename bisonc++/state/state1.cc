#include "state.ih"

State::State(size_t idx)
:
    d_nKernelItems(0),
    d_nTransitions(0),
    d_nReductions(0),
    d_defaultReducible(string::npos),
    d_maxLAsize(0),
    d_summedLAsize(0),
    d_idx(idx),
    d_nTerminalTransitions(0),
    d_srConflict(d_nextVector, d_itemVector, d_reducible),
    d_rrConflict(d_itemVector, d_reducible),
    d_stateType(StateType::NORMAL)
{}
