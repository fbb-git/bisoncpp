#include "terminal.ih"

namespace {
    char const *quotes[][2] = 
    {
        {"`", ""},
        {"'", ""}
    };
}

ostream &Terminal::quotedName(ostream &out) const
{
    size_t qIdx = (d_readableLiteral[0] == '\'');

    return out << quotes[0][qIdx] << d_readableLiteral << quotes[1][qIdx];
}

