#include "rules.ih"

void Rules::termToNonterm(Symbol *term, Symbol *nonTerm)
{
    d_terminal.erase(find(d_terminal.begin(), d_terminal.end(), term));

    Production::TermToNontermContext t2n = {term, nonTerm};

    for_each(d_production.begin(), d_production.end(), 
        FnWrap1c<Production *, Production::TermToNontermContext &>
                (Production::termToNonterm, t2n));
    
    delete term;
}
