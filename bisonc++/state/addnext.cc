#include "state.ih"

void State::addNext(Symbol const *symbol, size_t idx)
{
    d_itemVector[idx].setNext(d_nextVector.size());

                    // then add symbol to d_nextVector
    d_nextVector.push_back(Next(symbol, idx));  

                    // add all production rules of `symbol' to
                    // d_itemVector.
    if (symbol->isNonTerminal())        // set dependent elements
        addProductions(symbol, idx);
    else
        ++d_nTerminalTransitions;
}
