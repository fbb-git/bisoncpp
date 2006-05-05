#include "state.ih"

void State::addKernelItem(Item const &item)
{
    d_kernel.push_back(item);

    transitionOf(item.lhs());           // define an empty transition
                                        // or use an existing one

    msg() << indent << "Kernel item:" << info;
    msg() << incindent << spool;
    d_kernel.back().show();
    msg() << info;
    Indent::dec();
}
