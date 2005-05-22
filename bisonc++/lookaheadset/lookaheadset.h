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

        LookaheadSet &operator+=(LookaheadSet const &other);
        LookaheadSet &operator+=(FirstSet const &other);

        bool operator>=(LookaheadSet const &other) const;

        std::ostream &insert(std::ostream &out) const;
        bool hasEOF() const
        {
            return d_EOF;
        }        
    private:
};
                                // remove when insert() is virtual
std::ostream &operator<<(std::ostream &out, LookaheadSet const &LookaheadSet);
        
#endif
