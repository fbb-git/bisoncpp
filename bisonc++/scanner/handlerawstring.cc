#include "scanner.ih"

void Scanner::rawString()
{
    d_rawString = matched();
    d_rawString.erase(0, 1);        // rm the R

    d_rawString.front() = ')';      // end sentinel is )IDENTIFIER"
    d_rawString.back() = '"';

    more();
    begin(StartCondition__::rawstring);
}
