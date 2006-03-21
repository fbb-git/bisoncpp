#include "itemsets.ih"

// This function is part of the set of functions which determine whether a
// grammar derives any sentences. See derivesentence.cc

// called by `derive()'.

//  at shift:
//      when shifting to a not yet visited state, call derive() recursively
//      passing it the state to which we shift as its argument.

//  at reduce:
//      determine the length `l' of the rule, and consider StateInfo of the
//      state at stackdepth `l': if that N is not in d_processed, put it in
//      d_marked.

// at accept (NOT IN 0.98.004 !!!)
//      we're done, throw OK

void ItemSets::deriveAction(State::ActionTable::value_type const &action, 
                            ItemSets &itemSets)
{
    if (action.second.shift())
    {
        unsigned state = action.second.state();

        if (!itemSets.d_stateInfo[state].d_visited)
        {
            // cerr << "State " << state << 
            //         " not yet visited. Visiting now.\n";
            itemSets.derive(state);
        }
        // else
        //    cerr << "Skipping visited state " << state << endl;

        return;
    }

    if (action.second.reduce())
    {
        itemSets.deriveInspectReduction(action.second.production());
        return;
    }

    if (action.second.accept())
        throw true;

    msg() << "Internal Error in ItemSets::deriveAction():\n"
            "               action is not `shift',  `reduce' or `accept'" <<
            fatal;
}
