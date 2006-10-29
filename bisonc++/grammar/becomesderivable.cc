#include "grammar.ih"

bool Grammar::becomesDerivable(Production const *prod, Grammar &object)
{
        // get each nonterminal, underivable symbol
        // try to change it into a derivable symbol
        // return the success of this operation
        
    return 
        find_if(prod->begin(), prod->end(),
            Wrap1c<Symbol, Grammar, bool>(notDerivable, object))
        == prod->end();
}
