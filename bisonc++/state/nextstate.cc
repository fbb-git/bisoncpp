#include "state.ih"

void State::nextState(Next &next)
{
    if (next.next() != string::npos)    // state is already defined
        return;                         // if next indicates so.

    Item::Vector kernel;
                                        // build a new kernel
    next.buildKernel(&kernel, d_itemVector);

    size_t idx = findKernel(kernel);    // return the next State's idx

    next.setNext(idx);                  // set the next state to go to from
                                        // here on Next's symbol

    if (idx == s_state.size())
        addState(kernel);               // create and add a new state
}



