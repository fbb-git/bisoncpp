#include "itemsets.ih"

// Find all (kernel) items having rhs containing  `. symbol'
// Add all these items as kernel items 'symbol .' to the destination state
// and compute the destination state's closure
// See dragon book p. 232

bool ItemSets::goTo(State *dest, State const &source, Symbol const &symbol) 
{
    if (!rightOfDot(dest, source, symbol))
        return false;                   // no rules with `. symbol' found

    msg() << "Handling " << symbol.display() << ": " << spool;

    if (&symbol == Rules::errorTerminal())
        dest->setErrorState();
    
    dest->closure();                    // and compute the state's closure.
    return true;
}
