#include "state.ih"

// called by: closure

void State::inspectProduction(
                Production const &production, unsigned dot, 
                LookaheadSet const &lookaheadSet)
{
    // If the element following the dot position of the rule's RHS is in {N}
    // process the item's RHS

    if (!production.size())
    {
            // An empty production is reduced. No further inspection required.

        d_defaultReduction = &production;
        setReduce(Rules::defaultTerminal(), &production);
        return;
    }

            // When the dot reaches the end of the production, no further
            // inspection is required either
    if (dot >=  production.size())
        return;


    // in this state, the elements before the dots are remembered, since they
    // are the transition elements to which the goto's will go. 

    // Therefore, I add the current symbol at the dot position and (in
    // addImpliedNonTerminal()) all the initial elements of the state's
    // non-kernel items.  

    // Fortunately, at addImpliedNonTerminal() this function is also called,
    // to add nonkernel rules to the current state. 
    // Therefore, the first elements of the production rules of the
    // nonterminals found there are automatically added to the gotoSet as
    // well.

    Symbol const &symbol = production[dot];

    symbol.used();

    d_gotoSet.insert(&symbol);          // add the element as gotoSymbol.

    if (symbol.isTerminal())            // don't add terminal symbols to 
    {                                   // closure

        if (&symbol == Rules::errorTerminal())
            d_type = HAS_ERROR_ITEM;

        return;
    }


    // It this point we know that the symbol n beyond the . is an N

    // compute FIRST for the rhs beyond n
    LookaheadSet firstSet;
    findFirst(&firstSet, production.begin() + dot + 1, production.end(),
                    lookaheadSet); 

    // Add n to the Nonkernel set, then add the N's at the beginning of 
    // n's rules as well
    NonTerminal const *np = NonTerminal::downcast(&symbol);

    if (addToNonKernelSet(&firstSet, np))
        addImpliedNonterminals(np, firstSet);    
}






