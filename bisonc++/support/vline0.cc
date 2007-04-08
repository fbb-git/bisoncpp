#include "support.ih"

void Support::vline() const
{
    vline(nColumns());
    out() << "\n";
}

