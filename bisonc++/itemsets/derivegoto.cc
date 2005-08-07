#include "itemsets.ih"

// (Having visited all actions: while there are elements in d_marked:)
//  if the N shifts to the accepting state: throw `true': the grammar
//      is able to derives a sentence.
//  remove the N from d_marked, add it to d_processed;
//  then call derive() recursively passing it the state to which we shift as
//  its argument. 

void ItemSets::deriveGoTo(StateInfo &stateInfo, unsigned state)
{
    Symbol const *nonTerminal = *stateInfo.d_marked.begin();

    state = d_state[state]->gotoState(NonTerminal::downcast(nonTerminal));
    
    // cerr << "NonTerminal `" << nonTerminal->display() << 
    //        "' shifts to state " << state << endl;

    if (d_state[state]->acceptState())
    {
        // cerr << "Grammar derives a sentence" << endl;
        throw true;
    }

    stateInfo.d_marked.erase(nonTerminal);      // remove as N to inspect
    stateInfo.d_processed.insert(nonTerminal);  // register as processed N 

    derive(state);    
}
