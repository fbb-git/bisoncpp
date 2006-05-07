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
    {
        msg() << "LA-set not altered" << info;
        return;
    }

    d_construct = true;

    msg() << info;
    msg() << incindent << "expanding LA(" << 
                    lhs->display() << ") from\n" <<
                    incindent << lhsLA << "\n" << decindent << " to " << spool;

    lhsLA += la;            // define LA(lhs)
    msg() << lhsLA << info;
    Indent::dec();

    if (transition.influenceSize())
    {

        msg() << nlindent << "Inspecting influenced symbols:" << info;

        // Determine the LAs of all its dependent symbols (e.g., S, R)
        // 

        for_each(transition.influenceBegin(), transition.influenceEnd(),
            Wrap1c<Symbol, State>(inspectDepSym, *this));

        msg() << "\n" << info;
    }
}
