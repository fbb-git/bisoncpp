#include "grammar.ih"

bool Grammar::derivable(Symbol const *symbol)
{
    if (d_inspecting.find(symbol) != d_inspecting.end())
        return false;

    if 
    (
        symbol->isTerminal()
        ||
        d_derivable.find(symbol) != d_derivable.end()   // symbol is derivable
    )
        return true;

    d_inspecting.insert(symbol);

    Production::Vector const &productions =             // get all productions
        NonTerminal::downcast(symbol)->productions();   // of `symbol'

                                // if there is already a derivable production
                                // then `symbol' is derivable.
    bool ret = 
            find_if(
                productions.begin(), productions.end(),
                [this](Production const *prod)
                {
                    return isDerivable(prod);
                }
            ) 
            != productions.end()
        ||
            find_if(
                productions.begin(), productions.end(),
                [&](Production const *prod)
                {
                    return becomesDerivable(prod);
                }
            )
            != productions.end();

    if (ret)
        d_derivable.insert(symbol);

    d_inspecting.erase(symbol);
    return ret;
}




