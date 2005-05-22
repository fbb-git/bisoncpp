#include "state.ih"

State::State(Item const &item)
:
    d_kernel(1, item),
    d_inheritedTerminal(Rules::defaultTerminal()),  // no inheritedTerminal 
                                                    // so far.
    d_type(NORMAL),
    d_defaultReduction(0),
    d_nShiftReduceConflicts(0),
    d_nReduceReduceConflicts(0)
{}
