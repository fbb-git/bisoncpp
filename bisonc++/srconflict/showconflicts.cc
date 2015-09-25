#include "srconflict.ih"

void SRConflict::showConflicts(Rules const &rules) const
{
    RmReduction::ConstIter iter = d_rmReduction.begin();
    RmReduction::ConstIter end = d_rmReduction.end();

    unordered_map<size_t, vector<Symbol const *>> conflict;

    while ((iter = find_if(iter, end, RmReduction::isForced)) != end)
    {
        conflict[d_itemVector[iter->idx()].nr()].push_back(iter->symbol());
        ++iter;
    }

    if (conflict.empty())
        return;

    for (auto &rule: conflict)
    {
        auto prodPtr = rules.productions()[rule.first - 1];

        wmsg << "   rule " << rule.first << 
                     " (" << prodPtr->fileName() << ", line " <<
                             prodPtr->lineNr() << "): shifts at ";

         for (Symbol const *symbol: rule.second)
             wmsg << symbol << ", ";
    }
    wmsg << '\n';
}



