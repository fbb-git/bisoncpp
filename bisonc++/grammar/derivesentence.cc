#include "grammar.ih"

void Grammar::deriveSentence()
{
                                    // set up the stateInfo. the stack is
                                    //  still empty.
    prepareDerivation();            // preparation of the derivation
    
    if (!derive())
        msg() << 
            "Grammar's start symbol `" << Rules::startSymbol()->display() <<
            "' does not derive any sentence" << fatal;
}
