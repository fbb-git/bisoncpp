#include "state.ih"

// The LA sets of the items of a state (state tt(idx)) are computed by first
// computing the LA sets of its items, followed by propagating the LA sets of
// items to the states for which state transitions have been defined. 
//
//  1. A set (todo) contains the indices of the states whose LA sets must be
//      (re)computed. Initially it contains 0
//
//  2. First the LA sets of the state's items are computed, starting from the
//      LA sets of its kernel items. The LA set of each kernel item is
//      distributed (by distributeLAsetOf) over the items which are implied by
//      the item being considered. E.g., for item X: a . Y z, where a and z
//      are any sequence of grammar symbols and X and Y are non-terminal
//      symbols all of Y's production rules are added as new items to the
//      current state. 
//
//  3. The member distributeLAsetOfItem(idx) matches the item's rule
//      specification with the specification a.Bc, where a and c are (possibly
//      empty) sequences of grammatical symbols, and B is a (possibly empty)
//      non-terminal symbol appearing immediately to the right of the item's
//      dot position. if B is empty then there are no additional production
//      rules and distributeLAsetOf may return. Otherwise, the set b =
//      FIRST(c) is computed. This set holds all symbols which may follow
//      B. If b contains e (i.e., the element representing the empty set),
//      then the currently defined  LA set of the item can also be observed. In
//      that case e is removed, and the currently defined LA set is added to
//      b. Finally, the LA sets of all items representing a production rule
//      for B are inspected: if b contains unique elements compared to the LA
//      sets of these items, then the unique elements of b are added to those
//      item's LA sets and distributeLAsetOfItem() is recursively called for
//      those items whose LA sets have been enlarged. 
//
//  4. Once the LA sets of the items of a state have been computed,
//      inspectTransitions() is called to propagate the LA sets of items from
//      where transitions to other states are possible to the affected items
//      of those other (destination) states. The member inspectTransitions()
//      inspects all Next objects of the current state's d_nextVector. Next 
//      objects hold 
//       - the state index of a state to transfer to from the current state
//       - a size_t vector of item transitions. Each element is the index of an
//         item in the current state (the source-item), its index is the index
//          of a (kernel) item of the state to transfer to (the destination
//          index). 
//      If the LA set of the destination item is enlarged from the LA set of
//      the source item then the LA sets of the destination state's items
//      must be recomputed. This is realized by inserting the destation
//      state's index into the `todo' set.
//
//  5. Once the `todo' set is empty all LA sets of all items have been
//      computed. 


namespace
{
    size_t zero;
}

void State::determineLAsets() 
{
    set<size_t> todo(&zero, &zero + 1); // initialize to the first State idx.

    while (not todo.empty())
    {
        auto iter = todo.begin();

        State &state = *s_state[*iter]; // determine LA sets of the items of
                                        // this state.
        todo.erase(iter);

        state.computeLAsets();          // compute the LA sets of `state's 
                                        // items

        state.inspectTransitions(todo); // possibly update the LA sets of
                                        // kernel items of states to which a
                                        // transition is possible from
                                        // `state'. If so, the indices of
                                        // those target states are inserted
                                        // into `todo', causing the LA sets of
                                        // their items to be recomputed.
    }
}
