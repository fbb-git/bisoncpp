#include "srconflict.ih"

void SRConflict::visitReduction(size_t idx, SRConflict &context)
{
    Next::ConstIter nextIter = context.d_nextVector.begin();
    
    while (true)
    {
        nextIter = 
            find_if(
                nextIter, context.d_nextVector.end(), 
                FnWrap1c<Next const &, LookaheadSet const &, bool>(
                    Next::inLAset, context.d_itemVector[idx].lookaheadSet())
            );

        if (nextIter == context.d_nextVector.end())
            return;

        context.processShiftReduceConflict(nextIter, idx);
        ++nextIter;
    }
}
