#include "state.ih"
    
    // Inspect all production rules stored at transmap[depsym]
    // E.g., determine LA(S) from inspect S* -> S .
    //
void State::inspectDepSym(Symbol const *depSym, State &state)
{
    msg() << nlindent << "Transitions on " << depSym->display() << ":" << 
                                                                    info;

    for_each
    (
        state.d_transition[depSym]->kernelBegin(), // each production rule
        state.d_transition[depSym]->kernelEnd(),
            Wrap1c<Item, State>(inspectLA, state)
    );
}
