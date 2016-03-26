#include "block.ih"

    // $<ID>-NR, ($<ID>-NR),
    // $<ID>-NR.   

#include <iostream>

void Block::IDindex(size_t lineNr, string const &text)
{
    size_t begin = text.find('<') + 1;
    size_t end = text.find('>');

cerr << "dollarIndex: " << text << ", " << text.substr(end + 1) << '\n';

    d_atDollar.push_back(
        AtDollar(text[0] == '(' ? AtDollar::DEREF : AtDollar::DOLLAR,
            length(), lineNr, text, text.substr(begin, end - begin), 
            stol(text.substr(end + 1))
        )
    );

    append(text);
}
