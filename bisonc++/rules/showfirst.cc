#include "rules.ih"

void Rules::showFirst() const
{
    msg() << "\n"
            "FIRST sets:\n" << 
            info;

    for_each(d_nonTerminal.begin(), d_nonTerminal.end(),
                                    &NonTerminal::showFirst);
}







