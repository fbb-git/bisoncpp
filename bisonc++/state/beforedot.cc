#include "state.ih"

// return true if `symbol' is present in the kernel-rules before the
// . position. This function is called by ItemSets::searchState() to determine
// whether we can shift to a destination state when we've seen `symbol'. I use
// `beforeDot' rather than `atDot', since in that case I would also have to
// inspect the non-kernel rules. Now that I know that the dot is not at the
// first (0-th) position, I can safely ignore the non-kernel rules. However,
// the start-rule may contain the . at pos. 0, but that's never a rule under
// consideration, since we're now going TO other states, and we never go TO
// the rule S' -> . S when seeing a terminal symbol. So, I don't have to check
// whether dot is larger than 0.


bool State::beforeDot(Symbol const &symbol) const
{
    return find_if(d_kernel.begin(), d_kernel.end(),
                    Wrap1c<Item, Symbol const, bool>
                               (&Item::ifBeforeDot, symbol))
            != d_kernel.end();
}

