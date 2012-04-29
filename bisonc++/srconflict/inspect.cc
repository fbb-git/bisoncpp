#include "srconflict.ih"

// Each reducible item index is passed to visitReduction() which handles an
// observed S/R conflict. See README.states-and-conflicts for a description of
// the conflict resolution process.

// called fm: State::checkConflicts

void SRConflict::inspect()
{
    for (auto idx: d_reducible)
        visitReduction(idx);
}


