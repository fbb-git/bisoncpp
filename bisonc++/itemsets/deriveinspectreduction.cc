#include "itemsets.ih"

// see deriveAction().

//  at reduce:
//      determine the length `l' of the rule, and consider StateInfo of the
//      state at stackdepth `l': if that N is not in d_processed, put it in
//      d_marked.

void ItemSets::deriveInspectReduction(Production const *production) 
{
    // cerr << "Reducing to " << production << 
    //         ", rule size = " << production->size() << 
    //         ", stack size = " << d_stack.size() << endl;

    unsigned state = *(d_stack.rbegin() + production->size());

    Symbol const *nonTerminal = production->lhs();
    StateInfo &stateInfo = d_stateInfo[state];

    if (!stateInfo.d_processed.count(nonTerminal)) 
    {
        // cerr << "To be processed: N " << nonTerminal->display() << 
        //         " in state " << state << endl;
        stateInfo.d_marked.insert(nonTerminal);
    }
    // else
    //     cerr << "N " << nonTerminal->display() << 
    //             " in state " << state << " was already processed" << endl;
}



