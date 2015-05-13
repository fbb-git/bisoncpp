#ifndef _INCLUDED_NEXT_
#define _INCLUDED_NEXT_

#include <iostream>

#include <iosfwd>
#include <vector>

#include "../enumsolution/enumsolution.h"
#include "../statetype/statetype.h"
#include "../symbol/symbol.h"
#include "../item/item.h"
#include "../stateitem/stateitem.h"

// The state to transit to on a given terminal symbol. Refer to
// README.states-and-conflicts for a more detailed description of the class
// Next.

class Next
{
    public:
        typedef Enum::Solution Solution;

        typedef std::vector<Next>       Vector;
        typedef Vector::iterator        Iterator;
        typedef Vector::const_iterator  ConstIter;

    private:
        friend std::ostream &operator<<(std::ostream &out, Next const &next);

        Symbol const *d_symbol;         // on this symbol we transit to state
                                        // d_next. 
        Symbol const *d_removed;        // if d_symbol == 0 and d_removed
                                        // isn't then this transition has been
                                        // removed, and d_removed holds the
                                        // original d_symbol value
        bool d_forced;                  // forced removal of shift transition
                                        // due to undefined precedence of a
                                        // production rule
        size_t d_next;                  // the index of the state to transit 
                                        // to on d_symbol. 

        std::vector<size_t> d_kernel;   // d_kernel[idx] contains the index of
                                        // an item in the `parent' state
                                        // (i.e., the state transiting to
                                        // state d_next on d_symbol) to
                                        // d_next's (kernel) item idx. So, the
                                        // number of kernel items in state
                                        // d_next is equal to d_kernel.size().

        StateType d_stateType;          // the type of the state 
    
        static std::ostream &(Next::*s_insertPtr)(std::ostream &out) const;

    public:
        Next();
        Next(Symbol const *symbol, size_t stateItemOffset);

        Solution solveByAssociation() const;
        Solution solveByPrecedence(Symbol const *productionSymbol) const;
        Symbol const *symbol() const;
        size_t next() const;
        std::vector<size_t> const &kernel() const;

        void buildKernel(Item::Vector *kernel, 
                         StateItem::Vector const &stateItem);
        void setNext(size_t next);

        std::ostream &transition(std::ostream &out) const;
        std::ostream &transitionKernel(std::ostream &out) const;
        void checkRemoved(std::ostream &out) const;
        Symbol const *pSymbol() const;

        static size_t addToKernel(Vector &next, Symbol const *symbol, 
                                  size_t stateItemOffset);

        bool hasSymbol(Symbol const *symbol) const;
        bool inLAset(LookaheadSet const &laSet) const;

        static void removeShift(RmShift const &rmShift, Vector &nextVector,
                                size_t *nRemoved);

        static void inserter(std::ostream &(Next::*insertPtr)
                                            (std::ostream &out) const);
};

inline std::vector<size_t> const &Next::kernel() const
{
    return d_kernel;
}

inline Symbol const *Next::symbol() const
{
    return d_symbol;
}

inline bool Next::hasSymbol(Symbol const *symbol) const
{
    return d_symbol == symbol;
}

inline Symbol const *Next::pSymbol() const
{
    return d_symbol ? d_symbol : d_removed;
}

inline size_t Next::next() const
{
    return d_next;
}

inline void Next::setNext(size_t next)
{
    d_next = next;
}

inline bool Next::inLAset(LookaheadSet const &laSet) const
{
    return laSet >= d_symbol;
}

inline void Next::inserter(std::ostream &(Next::*insertPtr)
                                         (std::ostream &out) const)
{
    s_insertPtr = insertPtr;
}


inline std::ostream &operator<<(std::ostream &out, Next const &next)
{
    return (next.*Next::s_insertPtr)(out);

    // Set by static void inserter(Next::*insertPtr)
    //  to 'transition' or 'transitionKernel'
}


#endif
