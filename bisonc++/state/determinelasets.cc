#include "state.ih"

// The LA sets of the items of a state (state tt(idx)) are computed by first
// computing the LA sets of its items, followed by propagating the LA sets of
// items to the states for which state transitions have been defined. Then,
// the LA sets are computed for all items of all modified states: 

// OBSOLETE:
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

//        static Vector       s_state;  vector of State *s
//        

void State::determineLAsets() 
{
    set<size_t> todo;
    todo.insert(0);             // start with the first element

    while (true)
    {
        auto iter = todo.begin();
        if (iter == todo.end())
            return;

        State &state = *s_state[*iter];
        todo.erase(iter);

        state.computeLAsets();
        state.inspectTransitions(todo);
    }
}







