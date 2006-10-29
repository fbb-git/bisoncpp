#include "writer.ih"

void Writer::reduction(ostream &out, StateItem const &stateItem)
{
    ReductionContext context = {stateItem.nr(), out};

    for_each(
        stateItem.lookaheadSet().begin(), stateItem.lookaheadSet().end(),
        Wrap1c<Element, ReductionContext>(reduction, context));

    if (stateItem.lookaheadSet().hasEOF())
        reduction(Rules::eofTerminal(), context);
}
