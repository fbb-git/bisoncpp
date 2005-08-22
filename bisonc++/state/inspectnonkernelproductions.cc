#include "state.ih"

    // Inspect all the state's nonkernel production productions.  For each
    // production, if `symbol' is its initial element, then it is added to the
    // destination, using the production's LA-set, and incremented
    // dot-position. 

    // Must have nonKernelValue as the first parameter, since it's put there
    // by for_each()

void State::inspectNonKernelProductions(NonKernelValue const &nonKernelValue,
                    IIContext &context)
{
    NonTerminal const *nonTerm = nonKernelValue.first;

    AISA0Context context2 = {context.dest, context.symbol, 
                             nonKernelValue.second};

    for_each(nonTerm->productions().begin(), nonTerm->productions().end(),
        Wrap1c<Production, AISA0Context>
                  (&State::addIfSymbolAt0, context2));
}

