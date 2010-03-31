#include "srconflict.ih"

void SRConflict::inspect()
{
    for_each(d_reducible.begin(), d_reducible.end(), 
        FnWrap::unary(visitReduction, *this));
}


