#include "state.ih"

bool State::onlyTrailingDotItems()
{
    bool onlyTrailingDots = true;

    MDORContext context = {&onlyTrailingDots, *this};

    for_each(d_kernel.begin(), d_kernel.end(), 
        Wrap1<Item &, MDORContext>(&State::midDotOrReduce, context));

    return onlyTrailingDots;
}
