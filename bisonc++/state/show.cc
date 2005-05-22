#include "state.ih"

void State::show() const
{
    showKernel();
    for_each(d_nonKernel.begin(), d_nonKernel.end(),
                                                  &State::showNonKernelItem);
    msg() << "Goto Symbol set:" << info;
    for_each(d_gotoSet.begin(), d_gotoSet.end(), &Symbol::displaySymbol);
    msg() << info;
}
