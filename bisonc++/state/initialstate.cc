#include "state.ih"

void State::initialState() 
{
        // construct the initial state. Start with S' -> . S
        // The start rule is obtained from Production::start()

    State &state = newState(NORMAL);

//    state.d_itemVector.resize(1);

        // Add the start production to the StateItem::Vector

    state.addKernelItem(StateItem(Item(Production::start())));

    state.d_itemVector[0].setLA(LookaheadSet(LookaheadSet::e_withEOF));
}
