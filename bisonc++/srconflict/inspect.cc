#include "srconflict.ih"

// Each reducible item index is passed to visitReduction() which will handle
// any observed S/R conflict. See visitreduction.cc or
// READEM.states-and-conflicts for a description of the conflict resolution
// process. 

void SRConflict::inspect()
{
    for (auto idx: d_reducible)
        visitReduction(idx);
}


