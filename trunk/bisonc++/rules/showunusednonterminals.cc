#include "rules.ih"

void Rules::showUnusedNonTerminals() const
{
    Msg::setWarning();
    for_each(d_nonTerminal.begin(), d_nonTerminal.end(), 
                                    &NonTerminal::unused);

    if (NonTerminal::notUsed())
        msg() << info;

    Msg::setWarning();
    for_each(d_nonTerminal.begin(), d_nonTerminal.end(), 
                                    &NonTerminal::undefined);

    if (NonTerminal::notDefined())
        msg() << info;
}
