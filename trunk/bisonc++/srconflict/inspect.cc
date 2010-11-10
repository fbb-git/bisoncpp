#include "srconflict.ih"

// Each reducible item index is passed to visitReduction() which will handle
// any observed S/R conflict. See visitreduction.cc or
// READEM.states-and-conflicts for a description of the conflict resolution
// process. 

void SRConflict::inspect()
{
    for_each(d_reducible.begin(), d_reducible.end(), 
        FnWrap::unary(visitReduction, *this));
}


