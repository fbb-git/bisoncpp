#include "scanner.ih"

void Scanner::multiCharQuote()
{
    emsg << "multiple characters in quoted constant " << d_matched << endl;
    d_number = 0;
}
