#include "itemsets.ih"

// deriveSentence() tries to derive a sentence from the analyzed grammar. The
// algorithm is a modified version of the shift-reduce parsing algorithm. Its
// description is as follows:

// First, data are prepared:
//  - a vector<unsigned> acting as a stack of state numbers
//  - a vector<StateInfo> holding the state info used during the search
//  process: 
//      - bool d_visited: indicating that the state has already been visited
//                        by derive()
//      - set<N> d_marked: a set of `marked' N symbols
//      - set<N> d_processed: a set of `processed' N symbols


// Next, the derive() member is called with the initial state number (0),
// holding the start-state (x$ -> .x). From this state, derive() will try to
// derive a sentence, meaning that it tries to reach the accepting-state. If
// it succeeds, the grammar is able to generate sentences, if not the grammar
// should not be used, as it doesn't derive sentences. 

// Here is a description of derive()'s algorithm:

// Push the state provided as argument on the stack, mark the state as
// `visited' (this may happen repeatedly during the process)
//
// Visit the state's actions:
//  at shift:
//      when shifting to a not yet visited state, call derive() recursively
//      passing it the state to which we shift as its argument.
//  at reduce:
//      determine the length `l' of the rule, and consider StateInfo of the
//      state at stackdepth `l': if that N is not in d_processed, put it in
//      d_marked.
//
// Having visited all actions: while there are elements in d_marked:
//  if the N shifts to the accepting state: throw `true': the grammar
//      is able to derives a sentence.
//  remove the N from d_marked, add it to d_processed;
//  then call derive() recursively passing it the state to which we shift as
//  its argument. 
//
// Pop the state from the stack

// If derive() terminates, no sentences can be derived from the grammar 

void ItemSets::deriveSentence()
{
    d_stateInfo.resize(d_state.size()); // set up the stateInfo. the stack is
                                        //  still empty.
    
    try
    {
        derive(0);
        msg() << 
            "Grammar's start symbol `" << Rules::startSymbol()->display() <<
            "' does not derive any sentence" << fatal;
    }
    catch (bool ok)
    {}
}

