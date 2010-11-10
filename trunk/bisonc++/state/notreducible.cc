#include "state.ih"

void State::notReducible(size_t idx)
{
    Symbol const *symbol = d_itemVector[idx].symbolAtDot();

    symbol->used();     // For the showused bookkeeping

    if (symbol == Rules::errorTerminal())
        d_stateType.setType(StateType::ERR_ITEM);

    Next::ConstIter next;
    if (nextContains(&next, symbol)) // the symbol is in d_nextVector
        addDependents(*next, symbol, idx);
    else                            // symbol not yet in d_nextVector
        addNext(symbol, idx);
}

