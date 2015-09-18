#include "block.hh"

    // $<ID>$
void Block::IDdollar(size_t lineNr, string const &text)
{
    size_t begin = text.find('<') + 1;

    d_atDollar.push_back(
        AtDollar(
            AtDollar::DOLLAR, length(), lineNr, 
            text, text.substr(
                    begin, 
                    text.find('>') - begin
                  ), 
            numeric_limits<int>::max()
        )
    );

    append(text);
}
