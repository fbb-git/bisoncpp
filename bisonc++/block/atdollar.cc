#include "block.ih"

void Block::atDollar(size_t lineNr, string const &text, bool assignment,
                    bool refByScanner)
{
    d_atDollar.push_back(AtDollar{length(), lineNr, text, refByScanner});

    d_assignment |= assignment;

    append(text);
}
