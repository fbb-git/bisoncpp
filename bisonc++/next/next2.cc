#include "next.ih"

Next::Next(Symbol const *symbol, size_t stateItemOffset)
:
    d_symbol(symbol),
    d_removed(symbol),
    d_forced(false),
    d_next(string::npos),
    d_kernel(1, stateItemOffset),
    d_stateType(StateType::NORMAL)
{}
