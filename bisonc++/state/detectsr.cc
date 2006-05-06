#include "state.ih"

void State::detectSR(TransitionMap::value_type &transition, SRContext &src)
{
    if (transition.first->isNonTerminal())
        return;                             // no SR conflict with N symbols

        // RR conflicts have already been solved, so any T symbol is used at
        // most once in a reductions. Consequently, a single find can be used
        // to detect a S/R conflict for a given T-symbol
        //
    ReduceMapIterator reduceIter =
        find_if(src.state.d_reduce.begin(), src.state.d_reduce.end(), 
            Wrap1c<ReduceMapValue, Symbol, bool>
                   (findTerminal, 
                    *const_cast<Symbol *>(transition.first)));

    if (reduceIter == src.state.d_reduce.end())  // Not found: no SR conflict
        return;                             // for terminal transition.first.

    if (!src.headerDisplayed)
    {
        src.headerDisplayed = true;
        msg() << "\n"
                "State " << src.state.d_idx << ": S/R conflict" << info;

    }

    msg() << indent << "S/R decision on " << 
                    transition.first->display() << ":\n" << 
                    incindent << "to state " << 
                                        transition.second->next() << "\n" <<
                    indentdec << "or reduce, using " << reduceIter->first << 
                                                                        info;

    // SR conflicts are solved as follows:
    //  1. The larger priority is selected over a smaller priority
    //  2. With equal priorities the association determines the action
    //  3. By default shift is selected. This is a true SR conflict

    if 
    (
        solveSRbyPriority(transition, src, reduceIter)
        ||
        solveSRbyAssociation(transition, src, reduceIter)
    )
        return;


    // True S/R conflict: use the default.

    SRConflict conflict(transition.first, transition.second->next(), 
                        reduceIter->first);

    src.state.d_srConflict.push_back(conflict);
    SRConflict::show(conflict);

    reduceIter->second -= transition.first; 

                                                // don't reduce on `terminal'
    msg() << nlindent << "Counted " << src.state.d_srConflict.size() << 
                " shift/reduce conflicts" << info;

    ++s_nShiftReduceConflicts;
}
