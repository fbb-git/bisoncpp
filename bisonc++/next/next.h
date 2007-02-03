#ifndef _INCLUDED_NEXT_
#define _INCLUDED_NEXT_

#include <iosfwd>
#include <vector>

#include "../om/om.h"

#include "../srsolution/srsolution.h"
#include "../statetype/statetype.h"
#include "../symbol/symbol.h"
#include "../item/item.h"
#include "../stateitem/stateitem.h"

class Next: public StateType, public SRSolution
{
    friend std::ostream &operator<<(std::ostream &out, Next const &next);

    Symbol const *d_symbol;
    size_t d_next;
    std::vector<size_t> d_kernel;

    static std::ostream &(Next::*s_insert[])(std::ostream &out) const;


    public:
        typedef std::vector<Next>       Vector;
        typedef Vector::iterator        Iterator;
        typedef Vector::const_iterator  ConstIter;

        Next();
        Next(Symbol const *symbol, size_t stateItemOffset, Type type);

        Solution solveByAssociation() const;
        Solution solveByPrecedence(Symbol const *productionSymbol) const;
        Symbol const *symbol() const;
        size_t next() const;
        std::vector<size_t> const &kernel() const;

        void buildKernel(Item::Vector *kernel, 
                         StateItem::Vector const &stateItem);
        void setNext(size_t next);

        static size_t addToKernel(Vector &next, Symbol const *symbol, 
                                  size_t stateItemOffset);
        static bool hasSymbol(Next const &next, Symbol const *symbol);
        static bool inLAset(Next const &next, LookaheadSet const &laSet);

        static void removeShift(size_t idx, Vector &nextVector);

    private:
        std::ostream &insertStd(std::ostream &out) const;
        std::ostream &insertExt(std::ostream &out) const;
};

inline bool Next::hasSymbol(Next const &next, Symbol const *symbol)
{
    return next.d_symbol == symbol;
}

inline std::vector<size_t> const &Next::kernel() const
{
    return d_kernel;
}

inline Symbol const *Next::symbol() const
{
    return d_symbol;
}

inline size_t Next::next() const
{
    return d_next;
}

inline void Next::setNext(size_t next)
{
    d_next = next;
}

inline bool Next::inLAset(Next const &next, LookaheadSet const &laSet)
{
    return laSet >= next.d_symbol;
}

inline void Next::removeShift(size_t idx, Vector &nextVector)
{
    nextVector[idx].d_symbol = 0;
}

inline std::ostream &operator<<(std::ostream &out, Next const &next)
{
    return (next.*Next::s_insert[OM::type()])(out);
}


#endif
