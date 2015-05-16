#include "state.ih"

// Defining states proceeds like this:
//
//  0. The initial state is constructed. It contains the augmented grammar's
//     production rule. This part is realized by the static member
//
//          initialState();
//
//     The LA set of the kernel item of state 0 (the item representing the
//     augmented grammar's production rule `S_$: . S') is by definition equal
//     to $, representing EOF. This LA set is also initialized by
//     initialState().
//
//  1. Starting from the state's kernel item(s) all implied rules are added as
//     additional (non-kernel) state items. This results in a vector of
//     (kernel/non-kernel) items, as well as per item the numbers of the items
//     that are affected by this item. This information is used later to
//     compute the LA sets of the items. A set's items are determined from its
//     kernel items by the member
//          
//          setItems()
//
//     This member fills the StateItem::Vector vector. A StateItem contains
//
//         1. an item (production rule, dot position, LA set)
//         2. a size_t vector of `dependent' items, indicating which items
//            have LA sets that depend on the current item.
//         3. The size_t field `d_nextIdx' holds the index in d_nextVector,
//            allowing quick access of the d_nextVector element defining the
//            state having the current item as its kernel. a next of npos
//            indicates that the item does not belong to a next-kernel.
//
//     E.g., 
//
//     StateItem:
//     -------------------------------------
//     item        LA-set  dependent   next 
//                         stateitems  state
//     -------------------------------------
//     S* -> . S,  EOF,    (1, 2)      0    
//     ...
//     -------------------------------------
//
//     Also, the d_nextVector vector is filled.
//
//     A Next element contains
//
//          0. The symbol on which the transition takes place
//          1. The number of the next state
//          2. A StateItem::Vector object (size_t values) holding indices of 
//    items in the current state. The elements's indices are the indices of 
//    (kernel) items of the state to transfer to (the destination index).
//      E.g., 
//
//      Next:
//      -------------------------------
//      On          next    next kernel
//      Symbol      state   from items
//      -------------------------------
//      S           ?       (0, 1)
//      ...
//      -------------------------------
//
//     Empty production rules don't require special handling as they won't
//     appear in the Next table, since there's no transition on them.
//
//     From these facilities all states are now constructed. LA sets are
//     computed following the state construction by the member
//     determineLAsets. 
//
//  2. Then, from the Next::Vector constructed at (1) new states
//     are constructed. This is realized by the member
//
//          nextState()
//
//     which is called for each of the elements of d_nextVector.  States are
//     only constructed once. 
//
//  3. New states receive their kernel items from the item(s) of the current
//     state from where a transition is possible. A new state is constructed
//     by addState, receiving the just constructed set of kernel items from
//     nextState. 
//
//  4. All states are eventually constructed by the loop, shown below, which
//     ends once the idx loop control variable has reached s_state.size().
//
//  5. Once all  states have been constructed, the LA sets of the items of all
//     states are computed by determineLAsets(). See determinelasets.cc for a
//     discription of the implemented algorithm.
//
//  6. Once all states have been constructed and LA sets have been determined,
//     conflicts may be located and solved. If the state contains any conflict,
//     they are resolved and information about these conflicts is stored in an
//     SRConflict::Vector and/or RRConflict::Vector. Conflicts are identified
//     and resolved by the member (static)checkConflicts(); See
//     README.states-and-conflicts for a description of the actions taken by
//     checkConflicts().

void State::define(Rules const &rules)
{
    Arg &arg = Arg::instance();

    s_insert = arg.option(0, "construction") ?  &State::insertExt    :
               arg.option('V')               ?  &State::insertStd    :
                                                &State::skipInsertion;

    initialState();                 // construct the initial state
                                    // containing the augmented grammar's
                                    // StateItem

    size_t idx = 0;
    do
        s_state[idx]->construct();  // define all states (starting at state 0)
    while (++idx != s_state.size());

    // State 0's initial LA set is already set in initialSate.
    s_state[0]->determineLAsets();

    // Set the accept-state:
    //
    // The accept state is found as the state to transit to on the symbol
    // of the first item of the first (0-th) state. 
    // E.g., from S* -> . S it is the state to go to on S.
    // It is found from state[0]'s itemVector's zeroth element. Its next()
    // member returns the index in state[0]'s nextVector holding the
    // transition information of (e.g.) symbol S. So, that nextVector's
    // element's member next() tells us the accept state index.

    s_acceptState = 
        s_state[
            s_state[0]->d_nextVector[               
                s_state[0]->d_itemVector[0].next()  // Next from 1st item
            ].next()                                // next state from there
        ];                                          // state pointer itself

        // The rule start_$ -> start . is a spurious reduction. In fact no
        // such reduction may occur, since at that point EOF is obtained and
        // parsing should stop. Therefore, this reduction is removed.
    s_acceptState->d_reducible.erase(s_acceptState->d_reducible.begin());

        // REQ_TOKEN is the state's type because it terminates at EOF, and 
        // the EOF transition isn't interpreted as a terminal transition.
        // Other (terminal) transitions are possible too, so in this case 
        // a token is required anyway. Alternatively, keep NORMAL, and when
        // reaching this state and its type is NORMAL: ACCEPT. Pondering...
    s_acceptState->d_stateType.setType(StateType::REQ_TOKEN);

    for (auto state: s_state)
        state->checkConflicts();

    if 
    (
        SRConflict::nConflicts() + RRConflict::nConflicts() 
        != 
        Rules::expectedConflicts()
    )
    {
        if (SRConflict::nConflicts())
        {
            wmsg << SRConflict::nConflicts() << 
                    " Shift/Reduce conflict(s)\n";
            for (auto state: s_state)
                state->showSRConflicts(rules);       // inserts into wmsg
            wmsg << flush;
        }

        if (RRConflict::nConflicts())
        {
            wmsg << RRConflict::nConflicts() << 
                    " Reduce/Reduce conflict(s)" << '\n';
            for (auto state: s_state)
                state->showRRConflicts(rules);       // inserts into wmsg
            wmsg << flush;
        }
    }

    for (auto state: s_state)
        state->summarizeActions();
}




