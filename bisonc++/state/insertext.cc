#include "state.ih"

ostream &State::insertExt(ostream &out) const
{
    out << "State " << d_idx << ":\n";

    Terminal::inserter(&Terminal::plainName);
    NonTerminal::inserter(&NonTerminal::nameAndFirstset);
    Item::inserter(&Item::pNrDotItem);
    StateItem::inserter(&StateItem::itemContext);
    Next::inserter(&Next::transitionKernel);

    for (size_t idx = 0; idx < d_itemVector.size(); ++idx)
        out <<  idx << ": " << d_itemVector[idx] << endl;


    for (size_t idx = 0; idx < d_nextVector.size(); ++idx)
        out << "  " << idx << ": " << d_nextVector[idx] << endl;

    if (d_reducible.size())
    {
        out << "  Reduce item(s): ";
        copy(d_reducible.begin(), d_reducible.end(), 
            ostream_iterator<size_t>(out, " "));
        out << endl;                    
    }

    return out << d_srConflict << d_rrConflict << '\n';
}


