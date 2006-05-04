#include "grammar.ih"

void Grammar::reduce(StateInfo &state)
{
    d_token = d_stateInfo[d_state].lhs();

    for (unsigned idx = state.reductionSize(); idx--; )
            d_stack.pop_back();

    d_state = d_stack.back();
}
