#include "rrconflict.ih"

void RRConflict::showConflicts(Rules const &rules) const
{
    RRData::ConstIter iter = d_rmReduction.begin();
    RRData::ConstIter end = d_rmReduction.end();

    unordered_map<size_t, vector<size_t>> conflict;

    while ((iter = find_if(iter, end, RRData::isForced)) != end)
    {
        conflict[d_itemVector[iter->keepIdx()].nr()].push_back(
                        d_itemVector[iter->reduceIdx()].nr()
                    );
        ++iter;
    }

    if (conflict.empty())
        return;

    for (auto &rule: conflict)
    {
        auto prodPtr = rules.productions()[rule.first - 1];

        wmsg << "   keeping rule " << rule.first << 
                     " (" << prodPtr->fileName() << ", line " <<
                             prodPtr->lineNr() << "), dropping\n";

        for (size_t idx: rule.second)
        {
            prodPtr = rules.productions()[idx - 1];
            wmsg << "        rule " << idx << 
                     " (" << prodPtr->fileName() << ", line " <<
                             prodPtr->lineNr() << ")\n";
        }
    }
}



