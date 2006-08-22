#include "state.ih"

void State::checkSRConflict(Item &item, SRContext2 &src)
{
    msg() << "\nS/R Conflict test:" << info;
    item.show();
    msg() << "Reduction: " << src.reduction << info;

    // If no S/R conflict is found, then 
    // not (r.rhs == k.rhs  and r.LA >= k.dotSymOr0). 
    // Using DeMorgan's law: !(a && b) == !a || !b, I check for
    // r.rhs != k.rhs || ! (r.LA >= k.dotSymOr0)
    // If this is true, no S/R is detected and this function may return.

    if 
    (
        src.reduction->first->lhs() != item.lhs()
        ||
        !(src.reduction->second >= item.dotSymbolOr0())
    )
        return;

    if (!src.headerDisplayed)
    {
        src.headerDisplayed = true;
        msg() << "\n"
                "State " << src.state.d_idx << ": S/R conflict" << info;

    }

    TransitionMapValue &transition = 
                            *src.state.d_transition.find(item.dotSymbol());

    msg() << indent << "S/R decision on " << 
                    item.dotSymbol()->display() << ":\n" << 
                    incindent << "to state " << 
                                        transition.second->next() << "\n" <<
                    indentdec << "or reduce, using " << 
                                    src.reduction->first << info;

    // SR conflicts are solved as follows:
    //  1. The larger priority is selected over a smaller priority
    //  2. With equal priorities the association determines the action
    //  3. By default shift is selected. This is a true SR conflict

    if 
    (
        solveSRbyPriority(transition, src)
        ||
        solveSRbyAssociation(transition, src)
    )
        return;

    // True S/R conflict: use the default.

    SRConflict conflict(transition.first, transition.second->next(), 
                        src.reduction->first);

    src.state.d_srConflict.push_back(conflict);
    SRConflict::show(conflict);

    src.reduction->second -= transition.first; 

                                                // don't reduce on `terminal'
    msg() << nlindent << "Counted " << src.state.d_srConflict.size() << 
                " shift/reduce conflicts" << info;

    ++s_nShiftReduceConflicts;
}
