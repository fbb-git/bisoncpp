#include "state.ih"

// return true if `state' contains all items stored in `searchKernel'

bool State::hasKernel(State const *state, Item::Vector const &searchKernel)
{
    return state->d_nKernelItems == searchKernel.size() 
            &&
           searchKernel.size() ==
           static_cast<size_t>(
                count_if
                (
                    searchKernel.begin(), searchKernel.end(), 
                    FnWrap::unary(StateItem::containsKernelItem, 
                                 state->d_nKernelItems, state->d_itemVector)
                )
           );
}
