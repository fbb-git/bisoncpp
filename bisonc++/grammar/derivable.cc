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
        find_if(productions.begin(), productions.end(),
            Wrap1c<Production, Grammar, bool>(isDerivable, *this)
        )
            != productions.end()
        ||
        find_if(productions.begin(), productions.end(),
            Wrap1c<Production, Grammar, bool>(becomesDerivable, *this)
        ) 
            != productions.end();

    if (ret)
        d_derivable.insert(symbol);

    d_inspecting.erase(symbol);
    return ret;
}




