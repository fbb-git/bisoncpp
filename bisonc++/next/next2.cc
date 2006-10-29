#include "next.ih"

Next::Next(Symbol const *symbol, size_t stateItemOffset, Type type)
:
    StateType(type),
    d_symbol(symbol),
    d_next(string::npos),
    d_kernel(1, stateItemOffset)
{
}
