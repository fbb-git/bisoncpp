#include "block.ih"

void Block::atDollar(size_t lineNr, string const &text)
{
    d_atDollar.push_back(AtDollar{length(), lineNr, text});

    d_usedDollarDollar |= d_atDollar.back().dollarDollar();

    append(text);
}
