#include "state.ih"

    // return the index of this State's _error_ LA set in the laSet vector.
    // At this point it has already been determined that this state is an
    // ERROR state.
void State::errorLAset(LAsetVector &laSet)
{
    LookaheadSet set;

    for (StateItem const &item: d_itemVector)
    {
        Symbol const *symbol = item.symbolAtDot();

        if (symbol != 0 and symbol->value() == 0) // item at dot is _error_
        {
            set += item.lookaheadSet();

            if (item.lookaheadSet().hasEOF())
                set += Rules::eofTerminal();
        }
    }

    set -= Rules::errorTerminal();

    for (auto begin = laSet.begin(), end = laSet.end(); begin != end; ++begin)
    {
        if (*begin == set)                  // already existing set
        {
            d_LAsetIdx = begin - laSet.begin();   // set its index
            return;
        }
    }

    d_LAsetIdx = laSet.size();              // set a new index
    laSet.push_back(set);                   // insert a new set
}


