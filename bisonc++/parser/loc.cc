#include "parser.ih"

bool Parser::loc(int nElements, Block &block,AtDollar const &atd)
{
    block.replace(atd.pos(), atd.length(), s_locationValue);
    warnForceLSP(atd.lineNr());
    return false;
}
