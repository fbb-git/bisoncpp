#include "rules.ih"

void Rules::addRule(NonTerminal *np)
{
    lineMsg() << "Adding production rule for `" << np->name() << "'" << info;

    if (!d_startRule.length())
        d_startRule = np->name();

    d_currentRule = np;
}
