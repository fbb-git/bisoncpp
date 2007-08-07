#include "transition.ih"

void Transition::addShow(Item const &item)
{
    d_kernel.push_back(item);
    item.show();
    msg() << info;
}
