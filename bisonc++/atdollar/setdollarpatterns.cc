#include "atdollar.ih"

//          DD,             // $$
//          DDm,            // $$.
//          DDp,            // $$->
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

        case '<':
            setNumberPatterns();
        return;

        case '<':
            setTagPatterns();
        return;
{
            size_t end = d_text.find('>');
            d_tag = d_text.substr(2, end - 2);
            d_nr = stol(d_text.substr(end + 1));
            d_pattern = d_nr < 0 ? Dt_m;
        return;

        default:
            d_nr = stol(d_text.substr(1));
            d_pattern = d_nr < 0 ? D_m : Dnm;
        return;
    }

//    switch (d_text.back())
//    {
//        case '$':
//            d_pattern = DD;
//        return;
//
//        case '.':
//            memberSelectorPatterns();
//        return;
//
//        case '>':
//            pointerPatterns();
//        return;
//
//        default:
//            d_nr = stol(d_text.substr(1));
//            d_pattern = d_nr < 0 ? D_ : Dn;
//        return;
//    }
}
