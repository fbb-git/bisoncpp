#include "reductions.ih"

Reductions::Transition::Transition(unsigned prodNr)
:
    d_nr(prodNr),
    d_default_(false)
{}
