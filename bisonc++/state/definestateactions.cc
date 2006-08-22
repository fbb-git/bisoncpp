#include "state.ih"

    // Initally, the state holding S* -> S . was set to the accepting state.
    //
    // Next, multiple reductions are inspected for R/R conflicts. For
    // overlapping characters in their LAsets the conflict is solved:
    // Reduction to rule A is preferred over reduction to rule B if
    //  1. priority(A) > priority(B)        (explicitly defined priorities)
    //  2. rule A was defined earlier in the grammar. This is the default
    //      solution of a R/R conflict, and it represents a true conflict.
    // Overlapping characters are removed from the LA-sets of the ignored
    // reduction. 
    // 
    // Then, all terminal characters for which transitions are defined are
    // searched in the reduction LA-sets. 

// Note: this is not as it should be. It should be: all terminal characters
// which are at the dot-positions of the state's production rules are searched
// in the reduction's LA-sets. 

    // If such characters are found:
    //  reduce is preferred over shift if:
    //      the pri. of the reduction exceeds the priority of the shift
    //      the priorities are equal, but the association is left
    // In the opposite situation, shift is preferred (pri(R) < pri(S), or
    // R-association)
    // If no choice is made, shift is used, and a true S/R conflict is
    // reported. 
    // With shift, the terminal T is removed from the reduction's LA set
    // With reduce, the terminal's entry from the transitionMap is removed.
    // 
    // If, following the above decisions, a state has only one reduce action,
    // then the reduction becomes the default reduction.

void State::defineStateActions(State *state) 
{
    Indent::clear();

    state->solveReduceReduceConflicts();

    if (state == s_acceptState)
        state->tuneAcceptState();
    
    state->solveShiftReduceConflicts();

    for
    (
        ReduceMapIterator reduceIter = state->d_reduce.begin();
            reduceIter != state->d_reduce.end();
                ++reduceIter
    )            
    {
        if (!reduceIter->second.empty())
            continue;

        state->d_reduce.erase(reduceIter);
        reduceIter = state->d_reduce.begin();
    }

    if (state->d_reduce.size() == 1)
    {
        state->d_defaultReduction = state->d_reduce.begin()->first;
        state->d_reduce.clear();
    }
}
