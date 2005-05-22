#include "state.ih"

void State::addImpliedNonterminals(NonTerminal const *nt, 
                                    LookaheadSet const &firstSet)
{
    msg() << "    (all " << nt->name() << "-rules (dot = 0) " << 
            firstSet << ")" << info;

    d_nonKernel[nt] = firstSet;

    // Inspect the rhs of the rules of the N symbol. If they start with a N
    // then add those N's rules also to the closure.
    for
    (
        NonTerminal::ProdConstIter begin = nt->productions().begin(),
                              end = nt->productions().end();
            begin != end;
                ++begin
    )
        inspectProduction(**begin, 0, firstSet);
}
