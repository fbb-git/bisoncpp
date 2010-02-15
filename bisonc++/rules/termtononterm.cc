#include "rules.ih"

void Rules::termToNonterm(Symbol *term, Symbol *nonTerm)
{
    d_terminal.erase(find(d_terminal.begin(), d_terminal.end(), term));

    for_each(d_production.begin(), d_production.end(), 
        FnWrap::unary(Production::termToNonterm, term, nonTerm));
    
    delete term;
}
