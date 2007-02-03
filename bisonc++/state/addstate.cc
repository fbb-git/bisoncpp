#include "state.ih"

void State::addState(Item::Vector const &kernel, Type type)
{
    State &state = newState(type);

    for_each(kernel.begin(), kernel.end(), 
             FnWrap1c<Item const &, State &>(staticAddKernelItem, state));
}





