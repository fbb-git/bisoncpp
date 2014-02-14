#include "state.ih"

void State::summarizeActions()
{
    if ((d_nReductions = d_reducible.size()) != 0)
    {
        for (size_t idx = 0; idx != d_nReductions; ++idx)
        {
            StateItem const &stateItem = d_itemVector[idx];

            size_t laSize = stateItem.lookaheadSetSize();
    
            if (laSize < d_maxLAsize)           // add small LA sets to 
                d_summedLAsize += laSize;       //  summedLAsize
            else                                // default LA set becomes the
            {                                   //  largest and doesn't count
                d_summedLAsize += d_maxLAsize;  //  for summedLAsize, since
                d_maxLAsize = laSize;           //  all its elements collapse
                d_defaultReducible = idx;       //  into one element.
            }
        }
    }
}
