#ifndef _INCLUDED_RRCONFLICT_
#define _INCLUDED_RRCONFLICT_

#include <iosfwd>

#include "../stateitem/stateitem.h"
#include "../lookaheadset/lookaheadset.h"
#include "../rrdata/rrdata.h"

class Rules;

class RRConflict
{
    friend std::ostream &operator<<(std::ostream &out, 
                                    RRConflict const &conflict);

    StateItem::Vector const &d_itemVector;      // items involved in the RR
                                                // conflict 

    std::vector<size_t> const &d_reducible;     // the numbers of rules that
                                                // can be reduced 

    size_t d_firstIdx;                          // index of the first
                                                // reducible rule

    LookaheadSet const *d_firstLA;              // pointer to the LA set of
                                                // the first reducible rule
    
    RRData::Vector d_rmReduction;               // RRData of rules to remove

    static size_t  s_nConflicts;                // number of RR conflicts

    public:
        RRConflict(StateItem::Vector const &stateItem, 
                   std::vector<size_t> const &reducible);

        void inspect();
        void removeConflicts(StateItem::Vector &itemVector);

        static size_t nConflicts();

        void showConflicts(Rules const &rules) const;

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
