#include "atdollar.ih"

void AtDollar::setRefPatterns()     // text[0] == '_'
{
    switch (d_text[2])
    {
        case '<':
            d_pattern = refDt_;
            setTagNr(3);
        return;

        case '$':
            d_pattern = refDD;
        return;

        case '-':
            d_pattern = refD_;
        break;

        default:
            d_pattern = refDn;
        break;
    }

    d_nr = stol(d_text.substr(2));
}
