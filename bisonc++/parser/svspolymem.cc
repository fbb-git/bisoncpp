#include "parser.ih"

    // $nr. $-nr.
bool Parser::svsPolyMem(int nElements, Block &block, AtDollar const &atd)
{
    return svsPolyReplace(nElements, block, atd, ".");
}
