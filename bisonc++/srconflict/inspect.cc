#include "srconflict.ih"

// Each reducible item index is passed to visitReduction() which will handle
// any observed S/R conflict. See visitreduction.cc or
// READEM.states-and-conflicts for a description of the conflict resolution
// process. 

void SRConflict::inspect()
{
    for (size_t idx: d_reducible)
        visitReduction(idx);

//    for_each(
//        d_reducible.begin(), d_reducible.end(), 
//        [this](size_t idx)
//        {
//            this->visitReduction(idx);
//        }
//    );
}


