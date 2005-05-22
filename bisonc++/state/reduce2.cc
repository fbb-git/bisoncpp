#include "state.ih"

        // set d_action[each x in LookaheadSet] to reduce to the given rule
        // unless the state has only one (kernel) item: in that case reduce
        // unconditionally.

void State::reduce(Production const *production, 
                   LookaheadSet const &lookaheadSet)
{
    if 
    (
        d_kernel.size() == 1 
        && 
        production->nr() != Rules::acceptProductionNr()
    )
    {
        msg() << "  Single item kernel: reduce unconditionally" << info;
        d_defaultReduction = production;
        setReduce(Rules::defaultTerminal(), production);
        return;
    }

    for                             // it: iterator to Element const *,
    (                               //     actually a Terminal const *
        LookaheadSet::const_iterator it = lookaheadSet.begin();
            it != lookaheadSet.end();
                ++it
    )
        setReduce(Terminal::downcast(*it), production);

    if (lookaheadSet.hasEOF())
        setReduce(Rules::eofTerminal(), production);
}
