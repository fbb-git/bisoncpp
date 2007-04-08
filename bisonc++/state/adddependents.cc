#include "state.ih"

void State::addDependents(Next const &next, Symbol const *symbol, size_t idx)
{
    size_t nextIdx = Next::addToKernel(d_nextVector, symbol, idx);

    d_itemVector[idx].setNext(nextIdx);
                    
    if (symbol->isNonTerminal())    // set dependent elements
        d_itemVector[idx].setChildren(
            d_itemVector[next.kernel().front()].child()
        );
            // T-symbols don't have dependent elements, as only
            // N-symbols add new elements to d_itemVector
}
