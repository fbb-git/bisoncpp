#include "writer.ih"

void Writer::reduction(Table &table, StateItem const &stateItem)
{
    ReductionContext context = {stateItem.nr(), table};

    for_each(
        stateItem.lookaheadSet().begin(), stateItem.lookaheadSet().end(),
        FnWrap1c<Element const *, ReductionContext &>(reduction, context));

    if (stateItem.lookaheadSet().hasEOF())
        reduction(Rules::eofTerminal(), context);
}
