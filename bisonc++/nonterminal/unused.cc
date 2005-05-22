#include "nonterminal.ih"

void NonTerminal::unused(NonTerminal const *nonTerminal) 
{
    static bool header = false;

    if (!nonTerminal->isUsed())
    {
        if (!header)
        {
            msg() << 
                "Non-terminal symbol(s) not used in productions:" << warning;

            Msg::setWarning("");
            header = true;
        }
        msg() << "  " << nonTerminal->display() << warning;
    }
}
