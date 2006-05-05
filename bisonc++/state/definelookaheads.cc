#include "state.ih"

// Receive a LA. Use this LA for each kernel item

void State::defineLookaheads(LookaheadSet const &la) 
{
    msg() << nlindent <<
            "State " << d_idx << ": inspecting kernel items. LA: " << 
            la << info;

        // current state and provided LA
        //
    ItemContext itemContext = {*this, la};
    d_construct = false;

        // with, e.g., S* -> . S, inspect(S*, {$})
        // do this for all kernel items. 
        // inspectKernel calls state.inspect(item.lhs(), la)
        // 
    for_each(d_kernel.begin(), d_kernel.end(), 
        Wrap1c<Item, ItemContext>(inspectKernel, itemContext));

    if (!d_construct)
    {
        msg() << indent << "State " << d_idx << ": unchanged" << info;
        return;
    }

        // inspect all destination states
        // 
    for_each(d_transition.begin(), d_transition.end(), 
        Wrap1c<TransitionMapValue, TransitionMap>
                (propagateLookaheads, d_transition));

    Indent::dec();
    msg() << nlindent << 
        "State " << d_idx << ": LA inspection completed" << info;
}



