#include "state.ih"

ostream &State::insertExt(ostream &out) const
{
    OM::setType(OM::EXTENDED);

    out << "State " << d_idx << ":\n";

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

    OM::setType(OM::STD);

    return out << d_srConflict << d_rrConflict << "\n";
}



