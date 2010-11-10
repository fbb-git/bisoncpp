#include "stateitem.ih"

void StateItem::addProduction(Production const *production, 
                              StateItem::Vector &stateItem, size_t idx)
{
        // add another production at the end, make it depend on stateItem[idx]
    stateItem[idx].d_child.push_back(stateItem.size());

    stateItem.push_back(StateItem(Item(production)));
}
