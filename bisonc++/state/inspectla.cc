#include "state.ih"

    // E.g., determine LA(S) from inspect S* -> S .
    // Use LA(S*) as initial LA 

void State::inspectLA(Item &item, State &state)
{
    LookaheadSet laDot = 
        item.lookaheadFromDot(state.d_transition[item.lhs()]->lookaheadSet());

    msg() << nlindent << "Transition to " << spool;
    item.show();
    msg() << nlindent << "Inspecting productions of `" << 
                    item.symbolBeforeDot()->display() << "': " << spool;

    state.expandLookaheads(item.symbolBeforeDot(), laDot);
}
