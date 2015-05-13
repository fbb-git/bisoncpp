#include "state.ih"

//  Walk over all state items. See the tables below for an explanation
//
//  Production rules of N-symbols following the dot-position (e.g., S, L, R) 
//  are added to d_itemVector.
//
//  Each of these N symbols will be added to the state's d_nextVector (unless
//  it's already there).
//
//  If the symbol N is already in d_nextVector (addDependent()): 
//      1. the index of the item containing N (e.g., 0 for S, 1 for L) is
//          added to d_nextVector
//      2 the index of the N symbol in d_nextVector (e.g., 0 for S) is stored
//          in the itemVector's element containing the production rule of the N
//          symbol (for S: offset in d_next in d_itemVector[0] is 0).
//      3. the indices of all stateitems starting at N are stored in d_child:
//          these items depend on the item having N at dot (e.g., for S: 1, 2)
//
//  If the symbol is a new symbol (addNext()):
//      1. The N symbol's d_itemVector element's d_next offset is given the
//          size of d_nextVector (e.g., for S: 0, since there's no d_next
//          yet. In general: d_nextVector's size is the index of the next
//          element to be added to d_nextVector.
//      2. a new element is added to d_nextVector, containing the symbol, the
//          items's stateType, and the item's index in d_itemVector (e.g., for
//          S: Next(S, 0, type)
//
//  Terminal symbols will simply be added to d_nextVector, together with their
//  d_itemVector offsets (as they don't have production rules)
//
//  StateItems (in d_itemVector):
//  ------------------------------------------------------------
//  item            LA-set  dependent   offet in 
//                          stateitems  d_next
//  ------------------------------------------------
//  S* -> . S,      EOF,    (1, 2)      0
//  S  -> . L = R           (3,  )      1
//  S  -> . R
//  L  -> . * R
//  ... (etc)
//  ------------------------------------------------
//
//  Moreover, the Next vector will be adapted:
//
//  Next (in d_nextVector)
//  -------------------------------
//  On          next    next kernel
//  Symbol      state   from items
//  -------------------------------
//  S           ?       (0, 1)
//  L
//  R
//  *
//  ...
//  -------------------------------


void State::setItems()
{
    size_t idx = 0;                 // do not use a for stmnt here, as
                                    // notReducible may extend d_itemVector

    while (idx < d_itemVector.size())
    {
        if (d_itemVector[idx].isReducible())
            d_reducible.push_back(idx);
        else
            notReducible(idx);

        ++idx;              // inspect the next element
    }   
}
