#include "state.ih"

//        Walk over all state items. 
//
//        An N-symbol at the dot-position will have its production rules
//        added 
//
//        and d_nextVector will receive the N-symbol, as well as the
//        d_itemVector offsets containing the production rules, unless they're
//        already there. If they are already there, then d_nextVector will contain
//        its production rules, and so those production rules also depend on
//        the current d_itemVector[idx].  Terminal symbols will simply be
//        added to d_nextVector, together with their d_itemVector offsets (as they
//        don't have production rules)
//
//        StateItem:
//        -------------------------------------------
//        item            LA-enlarged LA-set  dependent 
//                                        stateitems
//        -------------------------------------------
//        S* -> . S,      false,      EOF,    (1, 2)
//        S  -> . L = R                       (3,  )
//        S  -> . R
//        L  -> . * R
//        ... (etc)
//        -------------------------------------------
//
//    Moreover, the Next vector will be adapted:
//
//        Next:
//        -------------------------------
//        On          next    next kernel
//        Symbol      state   from items
//        -------------------------------
//        S           ?       (0, 1)
//        L
//        R
//        *
//        ...
//        -------------------------------


void State::setItems()
{
    size_t idx = 0;

    while (idx < d_itemVector.size())
    {
        if (d_itemVector[idx].isReducible())
            d_reducible.push_back(idx);
        else
        {
            Symbol const *symbol = d_itemVector[idx].symbolAtDot();

            symbol->used();     // For the showused bookkeeping

            bool nonTerminal = symbol->isNonTerminal();      

            if (symbol == Rules::errorTerminal())
                setType(HAS_ERROR_ITEM);
                        
            Next::ConstIter next;
            if (nextContains(&next, symbol)) // the symbol is in d_nextVector
            {
                size_t nextIdx = Next::addToKernel(d_nextVector, symbol, idx);
                d_itemVector[idx].setNext(nextIdx);
                                
                if (type() == HAS_ERROR_ITEM)
                    d_nextVector[idx].setType(IS_ERROR_STATE);
                                        
                if (nonTerminal)            // set dependent elements
                    d_itemVector[idx].setChildren(
                        d_itemVector[next->kernel().front()].child());

                        // T-symbols don't have dependent elements, as only
                        // N-symbols add new elements to d_itemVector
            }
            else                            // symbol not yet in d_nextVector
            {
                d_itemVector[idx].setNext(d_nextVector.size());
                                
                                // then add symbol to d_nextVector
                d_nextVector.push_back(Next(symbol, idx, 
                    type() == HAS_ERROR_ITEM ? IS_ERROR_STATE : type()));

                                // add all production rules of `symbol' to
                                // d_itemVector.
                if (nonTerminal)                // set dependent elements
                    addProductions(symbol, idx);
                else
                    ++d_nTerminalTransitions;
            }
        }
        ++idx;              // inspect the next element
    }   
}






