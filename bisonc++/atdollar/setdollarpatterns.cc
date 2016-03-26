#include "atdollar.ih"

void AtDollar::setDollarPatterns()      // text[0] == '$'
{
    switch (d_text.back())
    {
        case '$':
            d_pattern = DD;
        return;

        case '.':
            memberSelectorPatterns();
        return;

        case '>':
            pointerPatterns();
        return;

        default:
            d_nr = stol(d_text.substr(1));
            d_pattern = d_nr < 0 ? D_ : Dn;
        return;
    }
}
