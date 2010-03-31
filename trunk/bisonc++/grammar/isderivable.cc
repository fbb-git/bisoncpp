#include "grammar.ih"

bool Grammar::isDerivable(Production const *prod, Grammar &object) 
{
    return 
        find_if(prod->begin(), prod->end(), 
            FnWrap::unary(notRemovable, object)) 
        == prod->end();
}

