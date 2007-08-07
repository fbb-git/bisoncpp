#include "nonterminal.ih"

void NonTerminal::undefined(NonTerminal const *nonTerminal) 
{
    if (nonTerminal->isUsed() && !nonTerminal->nProductions())
    {
        s_undefined = true;
        msg() << "No production rules for non-terminal `" <<
                 nonTerminal->name() << "'" << err;
    }
}
