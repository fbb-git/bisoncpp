#include "reductions.ih"

Reductions::iterator const Reductions::end() const
{
    if (!d_transitions.size())                      // no transitions
        return iterator(d_transitions.end());       // return end

                                                    // the last is the default
    if (d_defaultReduction == d_transitions.size() - 1)
        return iterator(d_transitions.end() - 1);   // return the last as end
        
    return iterator(d_transitions.end());           // return end() otherwise
}
