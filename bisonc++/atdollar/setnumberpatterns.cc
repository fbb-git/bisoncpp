#include "atdollar.ih"

//          Dn,             // $nr
//          Dnm,            // $nr.
//          Dnp,            // $nr->
//
//          D_,             // $-nr
//          D_m,            // $-nr.
//          D_p,            // $-nr->

void AtDollar::setNumberPatterns()
{
    d_nr = stol(d_text.substr(1));

    switch (d_text.back())
    {
        default:
            d_pattern = d_nr > 0 ? Dn : D_;
        return;

        case '.':
            d_pattern = d_nr > 0 ? Dnm : D_m;
        return;

        case '>':
            d_pattern = d_nr > 0 ? Dnp : D_p;
        return;
    }
}
