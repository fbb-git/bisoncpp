#include "state.ih"

void State::compareReductions(ReduceMapValue &first, 
                               RRContext &rrc)
{
    LookaheadSet intersection(first.second.hasEOF() && 
                                rrc.reduceIter->second.hasEOF());
    std::set<Element const *> &intersect = intersection;

    set_intersection(first.second.begin(),   first.second.end(),
                    rrc.reduceIter->second.begin(),  
                    rrc.reduceIter->second.end(),
                    inserter(intersect, intersect.begin()));

    if (intersection.empty())             // no overlap
        return;

    size_t/*unsigned*/ n = intersection.fullSize();

    if (!rrc.headerDisplayed)
    {
        rrc.headerDisplayed = true;
        msg() << "\n"
                "State " << rrc.idx << ": R/R conflict" <<
                (n == 1 ? "" :"s") << info;
    }

    if (!rrc.leftReductionDisplayed)
    {
        rrc.leftReductionDisplayed = true;
        msg() << decindent << "Comparing " << rrc.reduceIter->second << ":" << 
                                                                    info;
        Indent::inc();
    }

    msg() << indent << "to " << first.second << " (intersection: " << 
                            intersection << ")" << info; 

        // compare priorities of the productions

    Indent::inc();

    switch (Terminal::comparePriorities(first.first->precedence(),
                                    rrc.reduceIter->first->precedence()))
    {
        case Terminal::SMALLER:
            msg() << indent << "Removing " << intersection << 
                    "from LA of " << first.first << info;
            first.second -= intersection;
            Indent::dec();
        return;

        case Terminal::LARGER:
            msg() << indent << "Removing " << intersection << 
                    "from LA of " << rrc.reduceIter->first << info;
            rrc.reduceIter->second -= intersection;
            Indent::dec();
        return;

        default:
        break;
    }

    // Now we have a true RR conflict, which is solved by  
    // reducing to the rule defined first in the grammar

    RRConflict conflict(intersection, first.first, rrc.reduceIter->first);

    RRConflictVector &conflicts = s_state[rrc.idx]->d_rrConflict;
    conflicts.push_back(conflict);

    RRConflict::show(conflict);

    if (first.first->nr() < rrc.reduceIter->first->nr())
        rrc.reduceIter->second -= intersection;
    else
        first.second -= intersection;

    Indent::dec();
    msg() << nlindent << "Found " << n << " reduce/reduce conflict" <<
                                                (n == 1 ? "" : "s") << info;


    s_state[rrc.idx]->d_nRRConflicts += n;
    s_nReduceReduceConflicts += n; 
}






