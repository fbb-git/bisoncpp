#include "block.ih"

    // called at @@, $$, $$. or $$( in a block

void Block::dollar(size_t lineNr, string const &text, bool member)
{
    d_atDollar.push_back(
        AtDollar(
            text.back() == '(' ?    AtDollar::STYPE  :
            text[0] == '$' ?        AtDollar::DOLLAR : 
                                    AtDollar::AT, 
            length(), lineNr, 
            text, numeric_limits<int>::max(), member
        )
    );
    d_usedDollarDollar |= text[0] == '$';

    append(text);
}
