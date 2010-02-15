#include "writer.ih"

void Writer::reduction(Table &table, StateItem const &stateItem)
{
    size_t ruleNr = stateItem.nr();

    for_each(
        stateItem.lookaheadSet().begin(), stateItem.lookaheadSet().end(),
        FnWrap::unary(reductionSymbol, ruleNr, table));

    if (stateItem.lookaheadSet().hasEOF())
        reductionSymbol(Rules::eofTerminal(), ruleNr, table);
}
