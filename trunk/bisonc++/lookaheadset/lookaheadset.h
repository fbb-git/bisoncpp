#ifndef _INCLUDED_LOOKAHEADSET_
#define _INCLUDED_LOOKAHEADSET_

#include "../firstset/firstset.h"
#include "../terminal/terminal.h"

class LookaheadSet: private FirstSet
{               // 'Elements const ptrs' are known to be 'Terminal const ptrs'
    public:
        using FirstSet::begin;          // members from FirstSet made 
        using FirstSet::end;            // available for LookaheadSet

        enum EndStatus
        {
            e_withoutEOF,
            e_withEOF,
        };

    private:        
        EndStatus d_EOF;                // end-marker in the lookahead set

    public:
        FirstSet &firstSet();

        LookaheadSet(EndStatus eof = e_withoutEOF);
        LookaheadSet(FirstSet const &firstSet);
        LookaheadSet(LookaheadSet const &other);

        LookaheadSet &operator-=(LookaheadSet const &other);
        LookaheadSet &operator+=(LookaheadSet const &other);
        LookaheadSet &operator+=(FirstSet const &other);

        LookaheadSet &operator-=(Symbol const *symbol);

                        // true if *this contains other, 
                        // i.e., true if other has NO elements not already
                        // present in the current LookaheadSet
        bool operator>=(LookaheadSet const &other) const;

                        //  true if `symbol' is found in *this
        bool operator>=(Symbol const *symbol) const;
        bool operator<(LookaheadSet const &other) const;
        bool operator==(LookaheadSet const &other) const;

        std::ostream &insert(std::ostream &out) const;

        LookaheadSet intersection(LookaheadSet const &other) const;

        bool hasEOF() const;
        void rmEOF();
        bool empty() const;
        size_t fullSize() const;


    private:
        LookaheadSet(Element const **begin, Element const **end);
};

inline LookaheadSet::LookaheadSet(Element const **begin, Element const **end)
:
    FirstSet(begin, end)
{}

inline FirstSet &LookaheadSet::firstSet()
{
    return *this;
}

inline bool LookaheadSet::operator>=(Symbol const *symbol) const
{
    return find(symbol) != end();
}

inline bool LookaheadSet::operator<(LookaheadSet const &other) const
{
    return not (*this >= other);
}

inline bool LookaheadSet::hasEOF() const
{
    return d_EOF == e_withEOF;
}        

inline void LookaheadSet::rmEOF()
{
    d_EOF = e_withoutEOF;
}        

inline bool LookaheadSet::empty() const
{
    return d_EOF == e_withoutEOF && FirstSet::empty();
}

inline size_t LookaheadSet::fullSize() const
{
    return size() + (d_EOF == e_withEOF);
}

std::ostream &operator<<(std::ostream &out, LookaheadSet const &LookaheadSet);

#endif



