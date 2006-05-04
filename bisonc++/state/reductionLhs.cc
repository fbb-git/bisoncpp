#include "state.ih"

Symbol const *State::reductionLhs() const
{
    return d_defaultReduction ? d_defaultReduction->lhs() :
                                d_kernel[0].lhs();
}
