#include "itemsets.ih"

// see derive().

//  at shift:
//      when shifting to a not yet visited state, call derive() recursively
//      passing it the state to which we shift as its argument.

//  at reduce:
//      determine the length `l' of the rule, and consider StateInfo of the
//      state at stackdepth `l': if that N is not in d_processed, put it in
//      d_marked.

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

    msg() << "Internal Error in ItemSets::deriveAction():\n"
            "               action is neither `shift', nor `reduce'" <<
            fatal;
}
