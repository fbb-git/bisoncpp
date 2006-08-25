#include "grammar.ih"

Grammar::Action Grammar::action(StateInfo &state)
{
    if (state.isAcceptState())
        return ACCEPT;

    if (d_token)                // token obtained at reduce()
    {
        size_t/*unsigned*/ nextState = state.transit(d_token);
        if (nextState == d_state)
            return RETRY;

        d_state = nextState;
        return SHIFT;
    }

    if (state.hasDefaultReduction())    // state.reduce() ?
        return REDUCE;          // then reduce

    d_token = state.nextToken();        // get next token

    if (!d_token)                       // no more
        return NO_TRANSITIONS;

    size_t/*unsigned*/ nextState = state.transit(d_token);

    if (nextState == d_state)
        return RETRY;

    d_state = nextState;
    return SHIFT;
}




