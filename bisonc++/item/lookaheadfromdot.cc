#include "item.ih"

LookaheadSet Item::lookaheadFromDot(LookaheadSet const &current) const
{
    LookaheadSet la;    

    for 
    (
        size_t/*unsigned*/ dot = d_dot, size = productionSize();
            dot < size;
                ++dot
    )
    {
        la += (*d_production)[dot].firstSet();

        if (!la.hasEpsilon())
            return la;

        la.rmEpsilon();
    }

    if (!la.empty())                // some elements in la
    {
        if (!la.hasEpsilon())       // not contaiing epsilon, so no current
            return la;              // la can be added
        la.rmEpsilon();             // remove epsilon
    }

    la += current;                          // add current LAset if
                                            // la contains <e> at this point

    msg() << indent << "For " << spool;
    show();
    msg() << nlindent << "LA beyond dot " << d_dot << ": " << la << info;

    return la;
}





