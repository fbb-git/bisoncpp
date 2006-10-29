#include "grammar.ih"

bool Grammar::isDerivable(Production const *prod, Grammar &object) 
{
    return 
        find_if(prod->begin(), prod->end(), 
            Wrap1c<Symbol, Grammar, bool>(notRemovable, object)
        ) == prod->end();
}

