#include "grammar.ih"

bool Grammar::becomesDerivable(Production const *prod)
{
        // get each nonterminal, underivable symbol
        // try to change it into a derivable symbol
        // return the success of this operation
        
    return 
        find_if(
            prod->begin(), prod->end(),
            [&](Symbol const *symbol)
            {
                return not derivable(symbol);
            }
        )
        == prod->end();
}
