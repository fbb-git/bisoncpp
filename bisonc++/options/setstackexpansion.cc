#include "options.ih"

void Options::setStackExpansion(size_t stackExpansion)
{
    if (d_stackExpansion != 0)
        return;

    if (stackExpansion >= s_defaultStackExpansion)
        d_stackExpansion = stackExpansion;
}

