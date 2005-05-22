#include "state.ih"

    // incDot visits each of the kernel productions of the current state, and
    // increments its dot-position if symbol is at the current state's dot.
    // 

void State::incDot(State *dest, Symbol const &symbol) const
{
    IIContext context = {dest, symbol};

    for_each(d_kernel.begin(), d_kernel.end(),
        Wrap1<Item const &, IIContext>(&State::inspectItem, context));


    for_each(d_nonKernel.begin(), d_nonKernel.end(), 
        Wrap1<NonKernelValue const &, IIContext>
                  (&State::inspectNonKernelProductions, context));
}







