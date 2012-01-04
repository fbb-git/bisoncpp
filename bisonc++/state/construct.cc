#include "state.ih"

void State::construct()
{
    setItems();

    for (auto &next: d_nextVector)
        nextState(next);
}
