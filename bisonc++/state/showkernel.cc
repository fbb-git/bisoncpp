#include "state.ih"

void State::showKernel()
{
    for_each(d_kernel.begin(), d_kernel.end(), 
        Wrap1c<Item, TransitionMap>(showKernelLA, d_transition));
}
