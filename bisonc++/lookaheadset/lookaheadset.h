#ifndef _INCLUDED_LOOKAHEADSET_
#define _INCLUDED_LOOKAHEADSET_

#include "../firstset/firstset.h"
#include "../terminal/terminal.h"

class LookaheadSet: public FirstSet
{                   // Elements const ptrs are known to be Terminal const ptrs

    bool d_EOF;                             // end-marker in the lookahead set

    public:
        LookaheadSet(bool eof = false);
        LookaheadSet(FirstSet const &firstSet);
        LookaheadSet(LookaheadSet const &other);

        LookaheadSet &operator-=(LookaheadSet const &other);
        LookaheadSet &operator+=(LookaheadSet const &other);
        LookaheadSet &operator+=(FirstSet const &other);

        LookaheadSet &operator-=(Symbol const *symbol);

                        // true if *this contains other, 
                        // i.e., true if other has no new elements
        bool operator>=(LookaheadSet const &other) const;

                        //  true if `symbol' is found in *this
        bool operator>=(Symbol const *symbol) const
        {
            return find(symbol) != end();
        }
        bool operator<(LookaheadSet const &other) const
        {
            return not (*this >= other);
        }

        bool operator==(LookaheadSet const &other) const;

        std::ostream &insert(std::ostream &out) const;

        bool hasEOF() const
        {
            return d_EOF;
        }        
        void rmEOF()
        {
            d_EOF = false;
        }        
        bool empty() const
        {
            return !d_EOF && FirstSet::empty();
        }

        size_t/*unsigned*/ fullSize() const
        {
            return size() + d_EOF;
        }
};
                                // remove when insert() is virtual
std::ostream &operator<<(std::ostream &out, LookaheadSet const &LookaheadSet);
        
#endif



