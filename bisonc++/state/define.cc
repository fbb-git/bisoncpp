#include "state.ih"

// Defining states proceeds as follows:
//
//  0. The initial state is constructed. It contains the augmented grammar's
//     production rule. This part is realized by the static member
//
//          initialState();
//
//  1. From the state's kernel item(s) all implied rules are added as
//     additional state items. This results in a vector of (kernel/non-kernel)
//     items, as well as per item the numbers of the items that are affected
//     by this item. This information is used later on to propagate the
//     LA's. This part is realized by the member
//          
//          setItems()
//
//     This fills the StateItem::Vector vector. A StateItem contains
//
//         1. an item (production rule, dot position, LA set)
//         2. a LA-enlarged flag, raised when an item's LA set is enlarged
//         3. a size_t vector of `dependent' items, indicating which items
//            have LA sets that depend on the current item.
//         4. The size_t field `next' holds the index in d_nextVector,
//            allowing quick access of the d_nextVector element defining the
//            state having the current item as its kernel. a next of npos
//            indicates that the item does not belong to a next-kernel.
//
//     E.g., 
//
//     StateItem:
//     ---------------------------------------------------------------
//     item        LA-enlarged LA-set  dependent   next    next
//                                     stateitems  state   LA-enlarged
//     ---------------------------------------------------------------
//     S* -> . S,  false,      EOF,    (1, 2)      0       true/false
//     ...
//     ---------------------------------------------------------------
//
//     Also, the d_nextVector vector is filled.
//
//     A Next element contains
//
//          0. The symbol on which the transition takes place
//          1. The number of the next state
//          2. The indices of the StateItem::Vector defining the next
//                 state's kernel 
//      
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
//     Also, the nextOnSymbol() is handled here, and nextOnSymbol will simply
//     remove the production rules where dot is at the rule's end, since
//     they will not become part of the next state's kernels.
//      
//     Empty production rules don't require special handling as they won't
//     appear in the Next table, since there's no transition on them. Thus,
//     the previously mentioned nextOnSymbol() function is no longer
//     required. 
//
//     From these facilities all states are now constructed. LA propagation is
//     performed after the state construction since LA propagation is an
//     inherently recursive process, and state construction isn't. State
//     construction takes place below, in the while loop following the initial
//     state construction.
//
//  2. [cancelled: nextOnSymbol()]
//
//  3. Then the lookaheads (LAs)will be propagated over the items in the
//     current state. This is where previous versions went wrong. LAs are
//     distributed over and determined for each individual item, and are then
//     inherited by the next states. Also, LAs can be determined during the
//     construction of a state, instead of during a separate cycle. LAs are
//     propagated from the initial state over the dependent StateItems
//     Lookahead propagation is performed by the member
//                  
//          propagateLA()
//
//  4. Then, from the Next::Vector constructed at (1) the next states
//     are constructed. This is realized by the member
//
//          constructNext()
//
//     A next state will be constructed only if it wasn't constructed yet. For
//     a new state, the construct() member will be called. Construct() will
//     call setItems() and propagateLA(). Otherwise, propagateLA will also be
//     called for all states having kernels whose next LA-enlarged flag is
//     set. 

//  5. When all states have been constructed, conflicts are located and
//     solved. If the state contains any conflict, they are resolved and
//     information about these conflicts is stored in an SRConflict::Vector
//     and/or RRConflict::Vector. Conflicts are resolved by the member:
//
//          resolveConflicts();

void State::define()
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

    s_state[0]->propagateLA();      // propagate the LA set

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

    // The rule start_$ -> start . is a spurious reduction. In fact no such
    // reduction may occur, since at that point EOF is obtained and parsing
    // should stop. Therefore, this reduction is removed.

    s_acceptState->d_reducible.erase(s_acceptState->d_reducible.begin());

    // REQ_TOKEN is the state's type because it terminates at EOF, and 
    // the EOF transition isn't interpreted as a terminal transition.
    // Other (terminal) transitions are possible too, so in this case 
    // a token is required anyway. Alternatively, keep NORMAL, and when
    // reaching this state and its type is NORMAL: ACCEPT. Pondering...
    s_acceptState->setType(REQ_TOKEN);

    for_each(s_state.begin(), s_state.end(), staticCheckConflicts);

    if 
    (
        SRConflict::nConflicts() + RRConflict::nConflicts() 
        != 
        Rules::expectedConflicts()
    )
    {
        if (SRConflict::nConflicts())
            msg() << SRConflict::nConflicts() << 
                    " Shift/Reduce conflict(s)" << warning;

        if (RRConflict::nConflicts())
            msg() << RRConflict::nConflicts() << 
                    " Reduce/Reduce conflict(s)" << warning;
    }

    for_each(s_state.begin(), s_state.end(), staticSummarizeActions);
}





