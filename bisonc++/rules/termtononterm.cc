#include "rules.ih"

void Rules::termToNonterm(Symbol *term, Symbol *nonTerm)
{
    d_terminal.erase(find(d_terminal.begin(), d_terminal.end(), term));

    for (auto pPtr: d_production)
        Production::termToNonterm(pPtr, term, nonTerm);

    delete term;
}
