#include "state.ih"

void State::addKernelItem(StateItem const &stateItem)
{
    d_itemVector.push_back(stateItem);
    ++d_nKernelItems;
}
