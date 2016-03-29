#include "atdollar.ih"

//          DD,             // $$
//          DDm,            // $$.
//          DDp,            // $$->
//          DDpar,          // $$(
//
//          Dn,             // $nr
//          Dnm,            // $nr.
//          Dnp,            // $nr->
//
//          D_,             // $-nr
//          D_m,            // $-nr.
//          D_p,            // $-nr->
//
//          Dt_,            // $<TAG>-nr
//          Dt_m,           // $<TAG>-nr.
//          Dt_p,           // $<TAG>-nr->

void AtDollar::setDollarPatterns()      // text[0] == '$'
{
    switch (d_text[1])
    {
        case '$':
            setDollarDollarPatterns();
        return;

        default:
            setNumberPatterns();
        return;

        case '<':
            setTagPatterns();
        return;
    }
}







