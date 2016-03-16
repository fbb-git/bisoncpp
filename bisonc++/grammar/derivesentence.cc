#include "grammar.ih"

// Sentences are derived from the states following the Shift-Reduce algorithm
// trying all alternative routes until the final state is somehow reached.

void Grammar::deriveSentence()
{
    if (!derivable(Rules::startSymbol()))
        fmsg << 
            "Grammar's start symbol `" << Rules::startSymbol() <<
            "' does not derive any sentence" << noid;
}
