#include "state.ih"

void State::showKernel() const
{
    for_each(d_kernel.begin(), d_kernel.end(), &Item::showKernel);
}
