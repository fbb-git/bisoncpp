#include "scanner.ih"

void Scanner::assignment()
{
    d_block.atDollar(lineNr(), "_" + d_matched.substr(0, length() - 1));
    push("=");
}
