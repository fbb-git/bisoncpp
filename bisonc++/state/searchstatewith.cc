#include "state.ih"
    
    // searchStateWith() returns true if `state' has a kernel equal to
    // `kernel'. Since new states receive the kernels from their parents
    // the kernels of two states can simply be compared using == 
    //
bool State::searchStateWith(State &state, vector<Item> const &kernel)
{
    return kernel == state.d_kernel;
}
