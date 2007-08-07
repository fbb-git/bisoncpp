#include "state.ih"

ostream &State::insertStd(ostream &out) const
{
    out << "State " << d_idx << ":\n";

    for (size_t idx = 0; idx < d_nKernelItems; ++idx)
        out << d_itemVector[idx] << endl;

    for (size_t idx = 0; idx < d_nextVector.size(); ++idx)
        out << d_nextVector[idx] << endl;

    for (size_t idx = 0; idx < d_reducible.size(); ++idx)
        out << "  Reduce by " << d_itemVector[d_reducible[idx]] << endl;

    return out << d_srConflict << d_rrConflict << "\n";
}

