#include "state.ih"

// return the index of a state having all items listed in `searchKernel'. If
// no such state is found, return s_state's size.

size_t State::findKernel(Item::Vector const &searchKernel) const
{
    return find_if(s_state.begin(), s_state.end(),
                Wrap1c<State, Item::Vector, bool>(hasKernel, searchKernel))
           - s_state.begin();
}
