#include "state.ih"

// the kernel item of the first state has already been set bij initialState().

// setItems adds the items implied by the kernel item(s), and transitions to
// the next states.

void State::construct()
{
    setItems();

    for (auto &next: d_nextVector)
        nextState(next);
}
