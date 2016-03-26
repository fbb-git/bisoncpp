#include "atdollar.ih"

void AtDollar::setAtPatterns()      // text[0] == '@'
{
    if (d_text[1] == '@')
        d_pattern = AA;
    else
    {
        d_pattern = An;
        d_nr = stol(d_text.substr(1));
    }
}
