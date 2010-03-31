#include "nonterminal.ih"

void NonTerminal::unused(NonTerminal const *nonTerminal) 
{
    if (!nonTerminal->isUsed())
    {
        if (!s_unused)
        {
            msg() << 
                "Non-terminal symbol(s) not used in productions:" << warning;

            Msg::setWarning("");
            s_unused = true;
        }
        msg() << "  " << nonTerminal << warning;
    }
}
