#include "nonterminal.ih"

void NonTerminal::undefined(NonTerminal const *nonTerminal) 
{
    if (nonTerminal->isUsed() && !nonTerminal->nProductions())
        msg() << "No definition for non-terminal `" <<
                 nonTerminal->name() << "'" << err;
}
