#include "block.ih"

void Block::IDindex(size_t lineNr, string const &text)
{
    size_t begin = text.find('<') + 1;
    size_t end = text.find('>');

    d_atDollar.push_back(
        AtDollar(
            AtDollar::DOLLAR, length(), lineNr, 
            text, text.substr(begin, end - begin), stol(text.substr(end + 1))
        )
    );

    append(text);
}
