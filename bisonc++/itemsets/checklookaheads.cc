#include "itemsets.ih"

    // When transiting from the source state to the next state

    // 0.98.003->0.98.004:
    // d_recheckState is set to nextState only if `nextState' is smaller than
    // d_recheckState 

void ItemSets::checkLookaheads(unsigned nextState,  State const &source,
                               Symbol const &symbol)
{
    if 
    (
        d_state[nextState]->mergeLookaheads(source, symbol)
    )
    {
        if (d_recheckState < nextState)       // 0.98.003->0.98.004
            msg() << "Need to recheck reductions etc. from State " << 
                        nextState << " as well, but rechecks will "
                        "already start from state " << d_recheckState << info;
        else
        {
            msg() << "Recheck reductions and lookaheads from State " << 
                      nextState << info;
            d_recheckState = nextState;
        }
    }
}
