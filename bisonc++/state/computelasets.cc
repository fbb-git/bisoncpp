#include "state.ih"

void State::computeLAsets() 
{
    for_each(d_itemVector.begin(), d_itemVector.begin() + d_nKernelItems,
        [&](StateItem &kernelItem)
        {
            distributeLAsetOf(kernelItem);
        }
    );
}
