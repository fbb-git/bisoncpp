#include "atdollar.ih"

//          Dt_,            // $<TAG>-nr
//          Dt_m,           // $<TAG>-nr.
//          Dt_p,           // $<TAG>-nr->

void AtDollar::setTagPatterns()
{
    setTagNr(2);

    switch (d_text.back())
    {
        default:
            d_pattern = Dt_;
        return;

        case '.':
            d_pattern = Dt_m;
        return;

        case '>':
            d_pattern = Dt_p;
        return;
    }
}
