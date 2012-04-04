#include "block.ih"

    // called at $$ or $$. in a block

void Block::dollar(size_t lineNr, string const &text, bool member)
{
    d_atDollar.push_back(
        AtDollar(
            AtDollar::DOLLAR, length(), lineNr, 
            text, numeric_limits<int>::max(), member
        )
    );
    append(text);
}
