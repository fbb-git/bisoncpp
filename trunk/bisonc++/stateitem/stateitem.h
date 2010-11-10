#ifndef _INCLUDED_STATEITEM_
#define _INCLUDED_STATEITEM_

#include <iosfwd>
#include <vector>

#include "../symbol/symbol.h"
#include "../item/item.h"
#include "../lookaheadset/lookaheadset.h"
#include "../rmshift/rmshift.h"
#include "../rmreduction/rmreduction.h"
#include "../rrdata/rrdata.h"

// See also README.states-and-conflicts for a description of StateItem.
//
// A StateItem represents an item in one of the grammar's states. The
// information of a StateItem is displayed when --construction is used and is
// of a form like
//              0: [P1 1] S -> C  . C   { <EOF> }  0, (1 2 ) 0

class StateItem
{
    friend std::ostream &operator<<(std::ostream &out, 
                                    StateItem const &stateItem);

    Item    d_item;                 // The item
    LookaheadSet d_LA;              // its Lookahead set
    bool    d_LA_enlarged;          // true if enlarged (so check its
                                    // children)
    std::vector<size_t> d_child;    // offsets of its children (items added
                                    // because the current item is a N-symbol
    size_t  d_next;                 // offset in a Next array defining the 
                                    // next state (initialized to npos by
                                    // default)
    bool    d_nextEnlarged;         // true if its d_next item's LA set is 
                                    // enlarged.

    static std::ostream &(StateItem::*s_insertPtr)(std::ostream &out) const;

    public:
        typedef std::vector<StateItem> Vector;
        typedef Vector::const_iterator ConstIter;

        StateItem();
        StateItem(Item const &item);

        void setLA(LookaheadSet const &laSet);
        bool enlargeLA(LookaheadSet const &parentLA);

        size_t next() const;
        bool isReducible() const;
        Symbol const *symbolAtDot() const;
        Item const &item() const;
        std::vector<size_t> const &child() const;
        LookaheadSet const &lookaheadSet() const;
        size_t lookaheadSetSize() const;
        bool nextEnlarged() const;
        Production const *production() const;

        void setChildren(std::vector<size_t> const &dep);
        void setNext(size_t next);
        void clearNextEnlarged();

        Symbol const *precedence() const;   // a Terminal
        size_t nr() const;                  // the item's production number

        static void addProduction(Production const *production, 
                                  StateItem::Vector &stateItem,
                                  size_t idx);

        static bool propagateLA(StateItem &stateItem, Vector &vector);

        static bool containsKernelItem(Item const &item, 
                                       size_t nKernelItems,
                                       Vector const &vector);

        static bool lookaheadContains(StateItem const &stateItem,
                                      Symbol const *symbol);

        static void removeReduction(RmReduction const &rm,
                                    Vector &itemVector);
        static void removeRRConflict(RRData const &rm, Vector &itemVector);


        static void inserter(std::ostream &(StateItem::*insertPtr)
                                         (std::ostream &out) const);
        std::ostream &plainItem(std::ostream &out) const;
        std::ostream &itemContext(std::ostream &out) const;

    private:
        static void propagate(size_t idx, 
                              Vector &vector, LookaheadSet const &proposedLA);
};

inline bool StateItem::nextEnlarged() const
{
    return d_nextEnlarged;
}

inline LookaheadSet const &StateItem::lookaheadSet() const
{
    return d_LA;
}

inline size_t StateItem::lookaheadSetSize() const
{
    return d_LA.fullSize();
}

inline bool StateItem::isReducible() const
{
    return d_item.isReducible();
}

inline std::vector<size_t> const &StateItem::child() const
{
    return d_child;
}

inline Symbol const *StateItem::symbolAtDot() const
{
    return d_item.dotSymbolOr0();
}

inline void StateItem::setNext(size_t next)
{
    d_next = next;
}

inline size_t StateItem::next() const
{
    return d_next;
}

inline Item const &StateItem::item() const
{
    return d_item;
}

inline void StateItem::clearNextEnlarged()
{
    d_nextEnlarged = false;
}

inline Symbol const *StateItem::precedence() const
{
    return d_item.production()->precedence();
}

inline size_t StateItem::nr() const
{
    return d_item.production()->nr();
}

inline void StateItem::removeRRConflict(RRData const &rm,
                                       Vector &itemVector)
{
    itemVector[rm.reduceIdx()].d_LA -= rm.lookaheadSet();
}

inline void StateItem::removeReduction(RmReduction const &rm,
                                       Vector &itemVector)
{
    itemVector[rm.idx()].d_LA -= rm.symbol();
}

inline Production const *StateItem::production() const
{
    return d_item.production();
}

inline bool StateItem::lookaheadContains(StateItem const &stateItem, 
                                                   Symbol const *symbol)
{
    return stateItem.d_LA >= symbol;
}

inline void StateItem::inserter(std::ostream &(StateItem::*insertPtr)
                                         (std::ostream &out) const)
{
    s_insertPtr = insertPtr;
}


inline std::ostream &operator<<(std::ostream &out, StateItem const &stateItem)
{
    return (stateItem.*StateItem::s_insertPtr)(out);
}


#endif
