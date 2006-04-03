#include "reductions.ih"

Reductions::iterator const Reductions::begin() const
{
    if (!d_transitions.size())                  // no reductions: return end()
        return end();

                                                // otherwise, return begin
    return iterator(d_transitions.begin(), d_transitions.begin()->begin()); 
}
