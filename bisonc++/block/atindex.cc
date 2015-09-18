#include "block.hh"

    // @NR
void Block::atIndex(size_t lineNr, string const &text)
{
    d_atDollar.push_back(
        AtDollar(
            AtDollar::AT, length(), lineNr, 
            text, stol(text.substr(1)), false
        )
    );
    append(text);
}
