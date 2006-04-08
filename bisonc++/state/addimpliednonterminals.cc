#include "state.ih"



void State::addImpliedNonterminals(NonTerminal const *nt, 
                                    LookaheadSet const &firstSet)
{
    msg() << "    (all " << nt->name() << "-rules (dot = 0) " << 
            firstSet << ")" << info;

        // set the firstset for this NT
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
    {
        if ((*begin)->size() && &((**begin)[0]) == nt)    // left-recursive rule:
        {
            msg() << "   Not inspecting left-recursive rules of " << 
                    nt->name() << info;
            continue;                               // the N has already been
        }                                           // added
        inspectProduction(**begin, 0, firstSet);
    }
}
