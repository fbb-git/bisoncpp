#include "stateitem.ih"

bool StateItem::containsKernelItem(Item const &searchItem, 
                                   size_t nKernelItems, Vector const &vector)
{
    for (size_t idx = 0; idx != nKernelItems; ++idx)
        if (searchItem == vector[idx].d_item)
            return true;

    return false;
}
