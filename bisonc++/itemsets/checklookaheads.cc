#include "itemsets.ih"

    // When transiting from the source state to the next state
void ItemSets::checkLookaheads(unsigned nextState,  State const &source,
                               Symbol const &symbol)
{
    if (d_state[nextState]->mergeLookaheads(source, symbol))
    {
        msg() << "Recheck reductions and lookaheads from " << nextState << 
                info;
        d_recheckState = nextState;
    }
}
