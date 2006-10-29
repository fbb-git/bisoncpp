#include "state.ih"

void State::construct()
{
    setItems();

    for_each(d_nextVector.begin(), d_nextVector.end(),
        Wrap1c<Next, State>(nextState, *this));
}
