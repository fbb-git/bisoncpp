#include "state.ih"

// The LA set of an item tt(`idx') is distributed over the items representing
// production rules of the non-terminal to the right of item idx's dot
// position, using the following algorithm:

//     distributeLAsetOfItem(idx):
//         the item's production rule specification is matched with the
//         specification a.Bc, where a and c are (possibly empty) sequences of
//         grammatical symbols, and B is a (possibly empty) non-terminal
//         symbol appearing immediately to the right of the item's dot
//         position. 
// 
//         if B is empty return
// 
//         compute the set b = FIRST(c). 
// 
//         If b contains e (i.e., the element representing the empty set),
//         then add the item's current LA set to b.
// 
//         for each item `itm' containing a production rule for B
//         {
//             if b has unique elements compared to item itm's LA set
//             {
//                 add the unique elements of b to item itm's LA set
//                 distributeLAsetOfItem(itm).
//             }
//         }

void State::distributeLAsetOf(StateItem &stateItem) 
{
    Item const &item = stateItem.item();

    Symbol const *beyondDot = item.beyondDotIsNonTerminal();

    if (not beyondDot)                      // no additional rules if the item
        return;                             // byond the dot is not a
                                            // non-terminal symbol

    LookaheadSet candidate;                 // the candidate LA set for items
                                            // representing rules of symbol
                                            // beyondDot

                                            // FIRST(c) of rule a.Bc
                                            // if true, FIRST(c) contained
                                            // epsilon and so also receives 
                                            // current LA-set 
    if (item.firstBeyondDot(&candidate.firstSet()))
        candidate += stateItem.lookaheadSet();

    for (StateItem &stItem: d_itemVector)   // inspect all STATEitems of this
    {                                       // state
        if (
            stItem.lhs() == beyondDot       // if item is a productionrule of
            &&                              // B (= beyondDot)
            stItem.enlargeLA(candidate)     // and unique elements of
        )                                   // candidate could be added
            distributeLAsetOf(stItem);      // then distribute the updated LA
    }                                       // set of that state-item.
}











