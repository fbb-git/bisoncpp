#include "stateitem.ih"

bool StateItem::containsKernelItem(Item const &searchItem, 
                                   KernelContext const &context)
{
    for (size_t idx = 0; idx < context.nKernelItems; ++idx)
        if (searchItem == context.vector[idx].d_item)
            return true;

    return false;
}
