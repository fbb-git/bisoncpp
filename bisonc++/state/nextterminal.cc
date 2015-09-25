#include "state.ih"

Symbol const *State::nextTerminal(size_t *idxPtr) const
{
    size_t idx = *idxPtr;

    while (idx < d_nextVector.size())
    {
        Symbol const *ret = d_nextVector[idx].symbol();
        if (ret->isTerminal())
        {
            *idxPtr = idx;
            return ret;
        }
        ++idx;
    }
    return 0;
}
