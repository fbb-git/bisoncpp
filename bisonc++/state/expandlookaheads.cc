#include "state.ih"

    // Inspecting d_transition[lhs] of the current state
    // E.g., inspect(S*, $)
    //
    // Done if the LA hasn't changed
    // 
    //
void State::expandLookaheads(Symbol const *lhs, LookaheadSet const &la) 
{
    Transition &transition = *d_transition[lhs];
    LookaheadSet &lhsLA = transition.lookaheadSet();

    if (lhsLA >= la)    // no new items in lhs.la
        return;

    d_construct = true;

    msg() << indent << "Expanding LA(" << lhs->display() << ") from " <<
                    lhsLA << " to " << spool;
    lhsLA += la;            // define LA(lhs)
    msg() << lhsLA << info;

    if (transition.influenceSize())
    {

        msg() << nlindent << "Inspecting influenced symbols:" << info;

        // Determine the LAs of all its dependent symbols (e.g., S, R)
        // 

        Indent::inc();    

        for_each(transition.influenceBegin(), transition.influenceEnd(),
            Wrap1c<Symbol, State>(inspectDepSym, *this));

        Indent::dec();
        msg() << info;
    }
}
