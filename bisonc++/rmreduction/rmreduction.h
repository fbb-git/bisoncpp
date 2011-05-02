#ifndef _INCLUDED_RMREDUCTION_
#define _INCLUDED_RMREDUCTION_

#include <vector>
#include <cstddef>

class Symbol;

class RmReduction
{
    public:
        typedef std::vector<RmReduction>    Vector;
        typedef Vector::const_iterator      ConstIter;

    private:
        size_t  d_idx;              // idx in a StateItem::Vector of
                                    // reduce-production 
        size_t  d_next;             // next state when shifting
        Symbol const *d_symbol;     // symbol causing the S/R conflict
                                    
        bool   d_forced;            // forced if not based on precedence or
                                    // associativity 
    public:
        RmReduction() = default;    // Only needed for vectors
        RmReduction(size_t idx, size_t next, 
                    Symbol const *symbol, bool forced);

        size_t idx() const;
        size_t next() const;
        Symbol const *symbol() const;

        static bool isForced(RmReduction const &rmReduction);
};

inline size_t RmReduction::idx() const
{
    return d_idx;
}

inline Symbol const *RmReduction::symbol() const
{
    return d_symbol;
}

inline size_t RmReduction::next() const
{
    return d_next;
}

inline bool RmReduction::isForced(RmReduction const &rmReduction)
{
    return rmReduction.d_forced;
}

#endif
