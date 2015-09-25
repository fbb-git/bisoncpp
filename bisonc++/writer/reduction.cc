#include "writer.ih"

void Writer::reduction(Table &table, StateItem const &stateItem)
{
    size_t ruleNr = stateItem.nr();

    for (auto sym: stateItem.lookaheadSet())
        reductionSymbol(sym, ruleNr, table);

    if (stateItem.lookaheadSet().hasEOF())
        reductionSymbol(Rules::eofTerminal(), ruleNr, table);
}
