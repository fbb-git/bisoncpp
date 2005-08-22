#include "state.ih"

bool State::onlyTrailingDotItems()
{
    bool onlyTrailingDots = true;

    MDORContext context = {&onlyTrailingDots, *this};

    for_each(d_kernel.begin(), d_kernel.end(), 
        Wrap1c<Item, MDORContext>(&State::midDotOrReduce, context));

    if 
    (
        onlyTrailingDots 
        && 
        d_kernel[0].production().nr() == Rules::acceptProductionNr()
    )
    {
        s_acceptingState = d_idx;
        msg() << "   (ACCEPTING STATE)" << info;
    }

    return onlyTrailingDots;
}
