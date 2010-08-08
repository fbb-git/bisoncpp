#include "next.ih"

Next::Next()
:
    d_symbol(0),
    d_removed(0),
    d_forced(false),
    d_next(string::npos),
    d_stateType(StateType::NORMAL)
{}
