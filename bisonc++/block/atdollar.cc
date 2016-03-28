#include "block.ih"

void Block::atDollar(size_t lineNr, string const &text, bool assignment)
{
    d_atDollar.push_back(AtDollar{length(), lineNr, text});

    d_assignment |= assignment;

    append(text);
}
