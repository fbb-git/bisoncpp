#include "state.ih"

void State::findFirst(LookaheadSet *firstSet, Production::const_iterator begin,
                      Production::const_iterator const &end, 
                      LookaheadSet const &lookaheadSet) const
{
    for (; begin != end; ++begin)
    {
                        // add *begin's FIRST-set
        *firstSet += (*begin)->firstSet();

//      msg() << "{LA} (isn) is: " << *firstSet << info;

        if (!firstSet->hasEpsilon())        // no Epsilon in a firstset, then
        {
//          msg() << "{LA} is: " << *firstSet << info;
            return;                         // there's nothing more to add
        }
    }

    firstSet->rmEpsilon();
    *firstSet += lookaheadSet;              // add lookahead set
//  msg() << "{LA} includes initial {LA}: " << *firstSet << info;
}
