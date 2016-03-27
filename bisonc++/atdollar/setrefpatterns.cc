#include "atdollar.ih"

//          refDD,          // _$$
//          refDn,          // _$nr
//          refD_,          // _$-nr

void AtDollar::setRefPatterns()     // text[0] == '_'
{
    switch (d_text[2])
    {
        case '$':
            d_pattern = refDD;
        return;

        default:
            d_pattern = refDn;
        break;

        case '-':
            d_pattern = refD_;
        break;
    }

    d_nr = stol(d_text.substr(2));
}
