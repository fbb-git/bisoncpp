#include "nonterminal.ih"

void NonTerminal::undefined(NonTerminal const *nonTerminal) 
{
    if (nonTerminal->isUsed() && !nonTerminal->nProductions())
    {
        s_undefined = true;
        emsg << "No production rules for non-terminal `" <<
                 nonTerminal->name() << '\'' << endl;
    }
}
