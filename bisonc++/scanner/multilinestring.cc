#include "scanner.ih"

void Scanner::multiLineString()
{
    lineMsg(wmsg) <<
        "Multi-line strings are deprecated. Use string concatenation" << endl;
}
