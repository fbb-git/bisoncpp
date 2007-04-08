#include "state.ih"

void State::addState(Item::Vector const &kernel)
{
    State &state = newState();

    for_each(kernel.begin(), kernel.end(), 
         FnWrap1c<Item const &, State &>(staticAddKernelItem, state));
}





