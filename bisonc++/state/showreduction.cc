#include "state.ih"

void State::showReduction(ReduceMapValue const &reduction) 
{
    if (!reduction.second.empty())
        msg() << indent << 
            "On " << reduction.second << " reduce, using rule " <<
                reduction.first << info;
}
