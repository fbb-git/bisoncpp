#include "state.ih"

        // set d_action[each t in follow(LHS)] to reduce to that rule's nr.
        // unless the state has only one (kernel) item: in that case reduce
        // unconditionally.

void State::reduce(Item const &item)
{
    reduce(&item.production(), item.lookaheadSet());
}
