#include "state.ih"

void State::nextState(Next &next, State &state)
{
    if (next.next() != string::npos)    // state is already defined
        return;                         // if next indicates so.

    Item::Vector kernel;
                                        // build a new kernel
    next.buildKernel(&kernel, state.d_itemVector);

    size_t idx = state.findKernel(kernel);  // return the next State's idx

    next.setNext(idx);                  // set the next state to go to from
                                        // here on Next's symbol

    if (idx == s_state.size())
        state.addState(kernel);         // add a new state
}



