#include "rmreduction.ih"

RmReduction::RmReduction(size_t idx, size_t next, Symbol const *symbol,
                                bool forced)
:
    d_idx(idx),
    d_next(next),
    d_symbol(symbol),
    d_forced(forced)
{}
