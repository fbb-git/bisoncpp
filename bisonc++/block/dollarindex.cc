#include "block.hh"

    // $-?NR or $-?NR.

void Block::dollarIndex(size_t lineNr, string const &text, bool member)
{
    d_atDollar.push_back(
        AtDollar(AtDollar::DOLLAR, length(), lineNr, 
                 text, stol(text.substr(1)), member)
    );
    append(text);
}
