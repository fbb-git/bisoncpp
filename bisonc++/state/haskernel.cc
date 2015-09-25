#include "state.ih"

// return true if `state' contains all items stored in `searchKernel'

bool State::hasKernel(Item::Vector const &searchKernel) const
{
    return d_nKernelItems == searchKernel.size() 
            &&
           searchKernel.size() ==
           static_cast<size_t>(
                count_if
                (
                    searchKernel.begin(), searchKernel.end(), 
                    [&](Item const &searchItem)
                    {
                        return StateItem::containsKernelItem(searchItem,
                                d_nKernelItems, d_itemVector);
                    }
                )
           );
}
