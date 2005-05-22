#include "state.ih"

void State::showNonKernelItem(NonKernelValue const &nonKernel)
{
    msg() << "    " << nonKernel.first->name() << 
                "'s rules, using LA = " << nonKernel.second << info;
}
