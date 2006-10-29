#include "srconflict.ih"

void SRConflict::visitReduction(size_t const &idx, SRConflict &context)
{
    Next::ConstIter nextIter = context.d_nextVector.begin();
    
    while (true)
    {
        nextIter = 
            find_if(
                nextIter, context.d_nextVector.end(), 
                Wrap1c<Next, LookaheadSet, bool>(
                    Next::inLAset, context.d_itemVector[idx].lookaheadSet())
            );

        if (nextIter == context.d_nextVector.end())
            return;

        context.processShiftReduceConflict(nextIter, idx);
        ++nextIter;
    }
}
