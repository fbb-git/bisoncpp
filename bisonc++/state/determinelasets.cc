#include "state.ih"

// The LA sets of the items of a state (state tt(idx)) are computed by first
// computing the LA sets of its items, followed by propagating the LA sets of
// items to the states for which state transitions have been defined. Then,
// the LA sets are computed for all items of all modified states: 

// determineLAsetsOfState(idx): 
//     compute the LA sets of state idx's items.
// 
//     for each item `src' for which a transition to state `next' 
//     has been defined:
//     {
//         compute u = unique(src, next)
// 
//         if u is not empty then add u to the item matching item src in
//         state next, flagging state next as a modified state.
//     }
// 
//     for each flagged state `idx':
//         computeLAsetsOfState(idx)

void State::determineLAsets() 
{
    computeLAsets();            // compute the LA sets of this state's items
}







