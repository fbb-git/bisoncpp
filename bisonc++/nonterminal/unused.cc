#include "nonterminal.ih"

void NonTerminal::unused(NonTerminal const *nonTerminal) 
{
    if (!nonTerminal->isUsed())
    {
        if (!s_unused)
        {
            wmsg << "Non-terminal symbol(s) not used in productions:" << endl;
            s_unused = true;
        }
        wmsg << "  " << nonTerminal << endl;
    }
}
