#include "rrconflict.ih"

ostream &RRConflict::insert(ostream &out) const
{
    RRData::ConstIter iter = d_rmReduction.begin();
    RRData::ConstIter end = d_rmReduction.end();

    while ((iter = find_if(iter, end, RRData::isForced)) != end)
    {
        StateItem const &reduced = d_itemVector[iter->reduceIdx()];

        out << "Solved RR CONFLICT for rules " << 
                d_itemVector[iter->keepIdx()].nr() << " and " <<
                reduced.nr() << ":\n"
                "\tremoved " << iter->lookaheadSet() << 
                " from the LA set of " <<
                    (reduced.lookaheadSetSize() == 0 ? "(removed) " : "") <<
                "rule " << reduced.nr() << '\n';
        ++iter;
    }
    return out;
}
