#include "state.ih"

ostream &State::insertExt(ostream &out) const
{
    out << "State " << d_idx << ":\n";

        // set the ways the insertions must be done
    Terminal::inserter(&Terminal::plainName);
    NonTerminal::inserter(&NonTerminal::nameAndFirstset);
    Item::inserter(&Item::pNrDotItem);
    StateItem::inserter(&StateItem::itemContext);
    Next::inserter(&Next::transitionKernel);

        // display the items
    for (size_t idx = 0; idx != d_itemVector.size(); ++idx)
        out <<  idx << ": " << d_itemVector[idx] << '\n';

        // Next elements
    for (size_t idx = 0; idx != d_nextVector.size(); ++idx)
        out << "  " << idx << d_nextVector[idx] << '\n';

    if (d_reducible.size())
    {
        out << "  Reduce item(s): ";
        copy(d_reducible.begin(), d_reducible.end(), 
                                  ostream_iterator<size_t>(out, " "));
        out << '\n';                    
    }

    return out << d_srConflict << d_rrConflict << '\n';
}
