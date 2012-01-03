#include "rules.ih"

void Rules::termToNonterm(Symbol *term, Symbol *nonTerm)
{
    d_terminal.erase(find(d_terminal.begin(), d_terminal.end(), term));

    for (auto pPtr: d_production)
//    for_each(
//        d_production.begin(), d_production.end(), 
//        [=](Production *pPtr)
//        {
            Production::termToNonterm(pPtr, term, nonTerm);
//        }
//    );
    
    delete term;
}
