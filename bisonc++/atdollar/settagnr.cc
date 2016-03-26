#include "atdollar.ih"

void AtDollar::setTagNr(size_t begin)       // idx beyond <
{
    size_t end = d_text.find('>');

    d_tag = d_text.substr(begin, end - begin);
    d_nr = stol(d_text.substr(end + 1));
}


