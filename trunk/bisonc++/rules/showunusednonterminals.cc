#include "rules.ih"

void Rules::showUnusedNonTerminals() const
{
    wmsg.setTag("Warning");
    for_each(d_nonTerminal.begin(), d_nonTerminal.end(), 
                                    &NonTerminal::unused);

    if (NonTerminal::notUsed())
        imsg << endl;

    wmsg.setTag("Warning");
    for_each(d_nonTerminal.begin(), d_nonTerminal.end(), 
                                    &NonTerminal::undefined);

    if (NonTerminal::notDefined())
        imsg << endl;
}
