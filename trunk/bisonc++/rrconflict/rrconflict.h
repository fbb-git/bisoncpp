#ifndef _INCLUDED_RRCONFLICT_
#define _INCLUDED_RRCONFLICT_

#include <iosfwd>

#include "../stateitem/stateitem.h"
#include "../lookaheadset/lookaheadset.h"
#include "../rrdata/rrdata.h"

class RRConflict
{
    friend std::ostream &operator<<(std::ostream &out, 
                                    RRConflict const &conflict);

    StateItem::Vector const &d_itemVector;
    std::vector<size_t> const &d_reducible;

    size_t d_firstIdx;
    LookaheadSet const *d_firstLA;
    
    RRData::Vector d_rmReduction;

    static size_t  s_nConflicts;

    public:
        RRConflict(StateItem::Vector const &stateItem, 
                   std::vector<size_t> const &reducible);

        void inspect();
        void removeConflicts(StateItem::Vector &itemVector);

        static size_t nConflicts();

    private:
        std::ostream &insert(std::ostream &out) const;

        void visitReduction(size_t first);
        void compareReductions(size_t second);
};

inline size_t RRConflict::nConflicts()
{
    return s_nConflicts;
}

inline std::ostream &operator<<(std::ostream &out, RRConflict const &conflict)
{
    return conflict.insert(out);
}

        
#endif
