#include "parser.ih"

void Parser::done()
{
    lineMsg() << "Preamble (until %%) parsed" << info;

    throw 0;            // Saw %%, so done with parseUntilDoublePercent
}
