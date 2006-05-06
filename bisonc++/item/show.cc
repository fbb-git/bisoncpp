#include "item.ih"

void Item::show() const
{
    showKernel(*this, ")");
}
