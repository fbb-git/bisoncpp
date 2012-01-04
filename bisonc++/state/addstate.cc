#include "state.ih"

void State::addState(Item::Vector const &kernel)
{
    State &state = newState();

    for (auto &item: kernel)
        state.addKernelItem(StateItem(item));
}





