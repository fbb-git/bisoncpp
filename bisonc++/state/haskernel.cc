#include "state.ih"

// return true if `state' contains all items stored in `searchKernel'

bool State::hasKernel(State const *state, Item::Vector const &searchKernel)
{
    StateItem::KernelContext context = 
    {
        state->d_nKernelItems,
        state->d_itemVector
    };

    return state->d_nKernelItems == searchKernel.size() 
            &&
           searchKernel.size() ==
           static_cast<size_t>(
                count_if(searchKernel.begin(), searchKernel.end(), 
                    Wrap1c<Item, StateItem::KernelContext, bool>(
                        StateItem::containsKernelItem, context))
           );
}
