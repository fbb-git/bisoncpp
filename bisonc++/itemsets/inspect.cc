#include "itemsets.ih"

void ItemSets::inspect(unsigned idx)
{
    State &state = *d_state[idx];

    msg() << "\n"
            "Inspecting state " << idx << " having kernel items:" << info;

    state.showKernel();

        // if the rules only have trailing dots, then they cannot generate
        // new states, and we're done. 
        // For all trailing dot rules we can set the state's action map to 
        // REDUCE. 

    if (state.onlyTrailingDotItems())
        return;

    msg() << "Processing rules not ending at dot:" << info;

        // Walk along each of the grammar's symbols. If the goto() set
        // from `state' to that symbol is not empty and unique, add it
        // to d_state

    SSContext context = {*d_state[idx], *this};

    for_each(state.gotoSet().begin(), state.gotoSet().end(),
        Wrap1c<Symbol, SSContext>            
            (&ItemSets::searchState, context));
}






