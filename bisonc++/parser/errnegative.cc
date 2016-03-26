#include "parser.ih"

bool Parser::errNegative(int nElements, Block &block, AtDollar const &atd)
{
    emsg.setLineNr(atd.lineNr());
    emsg << atd.text() << ": " << atd.nr() << " requires tag" << endl;

    return false;
}
