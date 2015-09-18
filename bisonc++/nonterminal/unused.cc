#include "nonterminal.hh"

void NonTerminal::unused(NonTerminal const *nonTerminal) 
{
    if (!nonTerminal->isUsed())
    {
        if (!s_unused)
        {
            Global::plainWarnings();
            wmsg << "Non-terminal symbol(s) not used in productions:" << endl;
            s_unused = true;
        }
        wmsg << "  " << nonTerminal << endl;
    }
}
