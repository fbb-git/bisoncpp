#include "rules.ih"

void Rules::showFollow() const
{
    msg() << "\n"
            "FOLLOW sets:\n" << 
            info;

    for_each(d_nonTerminal.begin(), d_nonTerminal.end(),
                                    &NonTerminal::showFollow);
}
