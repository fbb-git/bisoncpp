#include "rules.ih"

    // following this call, d_currentRule points to the augmented grammar's 
    // startrule, which derives the startrule and has EOF in its FOLLOW set.

void Rules::augmentGrammar(Symbol *start)
{
    string augment = start->name() + "_$";

    newRule(insert(new NonTerminal(augment)), "-N.A.-", 0);
    addProduction(0);

    s_acceptProductionNr = d_currentProduction->nr();
    s_startSymbol = start;

    addElement(start);
    d_currentRule->used();
}
