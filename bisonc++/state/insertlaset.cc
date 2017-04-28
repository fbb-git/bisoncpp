#include "state.ih"

void State::insertLAset(ostream &out) const
{
    for (StateItem const &item: d_itemVector)
    {
        Symbol const *symbol = item.symbolAtDot();

        if (symbol != 0 and symbol->value() == 0)
            item.lookaheadSet().basicLAset(out);
    }
}
