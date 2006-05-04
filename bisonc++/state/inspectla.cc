#include "state.ih"

    // E.g., determine LA(S) from inspect S* -> S .
    // Use LA(S*) as initial LA 

void State::inspectLA(Item &item, State &state)
{
    Indent::inc();
    LookaheadSet laDot = 
        item.lookaheadFromDot(state.d_transition[item.lhs()]->lookaheadSet());

    msg() << indent << "Inspecting productions of `" << 
                    item.symbolBeforeDot()->display() << "'" << info;
    state.expandLookaheads(item.symbolBeforeDot(), laDot);
    Indent::dec();
}
