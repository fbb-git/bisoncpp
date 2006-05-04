#include "state.ih"

    // This function returns true if `item' is found in the kernel items of
    // `state'
bool State::searchItemIn(Item const &item, State &state)
{
    return find(state.d_kernel.begin(), state.d_kernel.end(), item) != 
        state.d_kernel.end();
}
