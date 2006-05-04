#include "state.ih"

void State::showNonKernelItem(Symbol const *nonKernel)
{
    msg() << indent << nonKernel->display() << "'s production rules" << info;
}
