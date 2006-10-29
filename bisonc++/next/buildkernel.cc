#include "next.ih"

void Next::buildKernel(Item::Vector *kernel, 
                       StateItem::Vector const &stateItem) 
{
    for (size_t idx = 0; idx < d_kernel.size(); ++idx)
        kernel->push_back(stateItem[d_kernel[idx]].item().incDot());
}
