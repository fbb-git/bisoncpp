#include "srconflict.ih"

ostream &SRConflict::insert(ostream &out) const
{
    RmReduction::ConstIter iter = d_rmReduction.begin();
    RmReduction::ConstIter end = d_rmReduction.end();

    while ((iter = find_if(iter, end, RmReduction::isForced)) != end)
    {
        out << "Solved SR CONFLICT on " << iter->symbol() << 
                ":\n"
                "\tshift to state " << iter->next() << ", removed " << 
                iter->symbol() << " from LA-set of rule " << 
                d_itemVector[iter->idx()].nr() << ")\n";
        ++iter;
    }

    return out;
}
