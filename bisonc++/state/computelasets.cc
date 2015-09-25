#include "state.ih"

// compute the LA sets of the items of a state.

// starting from the state's kernel items distribute their LA sets over the
// remaining items. See documentation/manual/algorithm/determine.yo

void State::computeLAsets() 
{
    for 
    (
        auto kernelItem = &d_itemVector[0], end = kernelItem + d_nKernelItems; 
            kernelItem != end;
                ++kernelItem
    )
        distributeLAsetOf(*kernelItem);
}
