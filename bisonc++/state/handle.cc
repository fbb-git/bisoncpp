#include "state.ih"

    // An item having a dot at its end is reduced.  Other items have their
    // LA's added to their lhs's LAset in d_transitions. The dot-incremented
    // item is stored with its original LAset in d_transitions in the entry
    // associated with the symbol over which the dot is moved. 

    // Inspection of the next state is called for when the item's lhs's LAset
    // is expanded with respect to the item's LAset.  When the inspection is
    // required, the item's LAset is given the value of the item's lhs's
    // LAset. 

void State::handle(Item const &item)
{
    Indent::inc();
    if (item.reduce())
    {
        msg() << indent << "Reduce by " << item.production() << info;
        d_reduce[&item.production()] = LookaheadSet();

        Indent::dec();
        return;
    }
                                // Get the symbol for the next transition
    Symbol const *symbol = item.dotSymbol();  

    symbol->used();             // For the showused bookkeeping

                                // get the associated Transition struct
    Transition *transition = transitionOf(symbol);

                                // NonTerminal: add next item
                                //              
    if (symbol->isNonTerminal())
    {
        msg() << indent << 
            "On NonTerminal `" << symbol->display() << "':" << info;

                                // determine transitions once.
        if (!transition->hasDestination() && !transition->productionsEntered())
        {
            d_nonKernel.push_back(symbol);

            msg() << incindent << "(adding production rules of `" << 
                    symbol->display() << "')" << info;
            Indent::dec();
        }
    }
    else
    {
        msg() << indent << "On Terminal " << symbol->display() << ":" << spool;

        if (symbol == Rules::errorTerminal())
            d_type = HAS_ERROR_ITEM;
    }

    msg() << indent << "to a state with kernel item:" << info;
    msg() << incindent << spool;
                                        // kernel item when shifting `symbol'
    transition->addShow(item.incDot());

    if (symbol->isNonTerminal())
    {
                                // transition[symbol] depends on item.lhs() 
        msg() << indent << "LA(" << item.lhs()->display() << 
                ") influences the LA used with the `" <<
             symbol->display() << "' transition" << info;

        transitionOf(item.lhs())->influences(symbol);
    }

    Indent::dec();
    Indent::dec();
}







