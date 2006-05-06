#include "terminal.ih"

Terminal::PriorityComparison 
    Terminal::comparePriorities(Terminal const *first, Terminal const *second)
{
    unsigned firstPriority = first ? first->d_priority : 0;
    unsigned secondPriority = second ? second->d_priority : 0;

    return firstPriority > secondPriority ?
                LARGER 
            : firstPriority < secondPriority ?
                SMALLER
            :
                EQUAL;

//    if (!first)
//        return !second || !second->d_priority ?  EQUAL : SMALLER;
//        
//    return !second  ? EQUAL : 
//                first->d_priority < second->d_priority ? SMALLER : LARGER;
}
