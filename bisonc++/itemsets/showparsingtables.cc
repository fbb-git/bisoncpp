#include "itemsets.ih"

void ItemSets::showParsingTables() const
{
    msg() << "\n"
             "GRAMMAR STATES:\n" << 
             info;

    for_each(d_state.begin(), d_state.end(), &State::showTables);
}

