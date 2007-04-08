#include "support.ih"

void Support::vline(size_t col) const
{
    if (col < sep().size())
        out() << sep()[col];
}

