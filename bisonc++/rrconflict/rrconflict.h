#ifndef _INCLUDED_RRCONFLICT_
#define _INCLUDED_RRCONFLICT_

#include <ostream>
#include <utility>

#include "../lookaheadset/lookaheadset.h"

class Production;

class RRConflict;

class RRConflict: private std::pair<Production const *, Production const *>
{
    LookaheadSet d_laSet;

    public:
        RRConflict()
        {}
        RRConflict(LookaheadSet const &laSet, 
                    Production const *one, Production const *other);
        LookaheadSet const &lookaheadSet() const
        {
            return d_laSet;
        }
        static void show(RRConflict const &conflict);
    private:
};


#endif
