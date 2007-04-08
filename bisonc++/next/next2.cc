#include "next.ih"

Next::Next(Symbol const *symbol, size_t stateItemOffset)
:
    StateType(NORMAL),
    d_symbol(symbol),
    d_next(string::npos),
    d_kernel(1, stateItemOffset)
{
}
