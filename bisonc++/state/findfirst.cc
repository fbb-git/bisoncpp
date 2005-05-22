#include "state.ih"

void State::findFirst(LookaheadSet *firstSet, Production::const_iterator begin,
                      Production::const_iterator const &end, 
                      LookaheadSet const &lookaheadSet) const
{
    for (; begin != end; ++begin)
    {
                        // add *begin's FIRST-set
        *firstSet += (*begin)->firstSet();

        if (!firstSet->hasEpsilon())        // no Epsilon in a firstset, then
            return;                         // there's nothing more to add
//            msg() << "LA-set is: " << *firstSet << info;
    }

    firstSet->rmEpsilon();
    *firstSet += lookaheadSet;              // add lookahead set
//    msg() << "LA-set is: " << *firstSet << info;
}
