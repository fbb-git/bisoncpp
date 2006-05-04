#include "terminal.ih"

Terminal::PriorityComparison 
    Terminal::comparePriorities(Terminal const *first, Terminal const *second)
{
    if (!first)
        return !second || !second->d_priority ?  EQUAL : SMALLER;
        
    return !second  ? EQUAL : 
                first->d_priority < second->d_priority ? SMALLER : LARGER;
}
