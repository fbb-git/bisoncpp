#ifndef _INCLUDED_SRCONFLICT_
#define _INCLUDED_SRCONFLICT_

#include <iosfwd>
#include <vector>

#include "../srsolution/srsolution.h"
#include "../rmreduction/rmreduction.h"
#include "../next/next.h"

class SRConflict: public SRSolution
{
    friend std::ostream &operator<<(std::ostream &out, 
                                    SRConflict const &conflict);

    Next::Vector const &d_nextVector;    
    StateItem::Vector const &d_itemVector;
    std::vector<size_t> const &d_reducible;
    
    RmReduction::Vector     d_rmReduction;
    std::vector<size_t>     d_rmShift;

    static size_t  s_nConflicts;

    public:
        SRConflict(Next::Vector const &next, 
                   StateItem::Vector const &stateItem, 
                   std::vector<size_t> const &reducible);

        void inspect();

                            // returns # of shifts that were removed
        size_t removeShifts(Next::Vector &nextVector);

        void removeReductions(StateItem::Vector &itemVector);

        static size_t nConflicts();

    private:
        std::ostream &insert(std::ostream &out) const;
        void processShiftReduceConflict(Next::ConstIter const &next, 
                                        size_t itemIdx);

        static void visitReduction(size_t idx, SRConflict &context);
};

inline size_t SRConflict::nConflicts()
{
    return s_nConflicts;
}

inline std::ostream &operator<<(std::ostream &out, SRConflict const &conflict)
{
    return conflict.insert(out);
}

#endif
