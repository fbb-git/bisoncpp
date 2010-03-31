#include "scanner.ih"

void Scanner::multiLineString()
{
    lineMsg() <<
        "Multi-line strings are deprecated. Use string concatenation" <<
        warning;
}
