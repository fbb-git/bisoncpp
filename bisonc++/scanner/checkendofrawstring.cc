#include "scanner.ih"

void Scanner::checkEndOfRawString()
{
    if (matched().rfind(d_rawString) == length() - d_rawString.length())
        begin(StartCondition__::block);

    more();
}
