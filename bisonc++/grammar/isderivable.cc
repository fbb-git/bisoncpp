#include "grammar.ih"

bool Grammar::isDerivable(Production const *prod) 
{
    return 
        find_if(
            prod->begin(), prod->end(), 
            [&](Symbol const *symbol)
            {                       // not removable if:
                return              // currently testing 
                    d_inspecting.find(symbol) != d_inspecting.end()
                    ||              // or a non-removable non-terminal
                    (
                        symbol->isNonTerminal() 
                        &&
                        d_derivable.find(symbol) == d_derivable.end());
            }
        )
        == prod->end();
}

