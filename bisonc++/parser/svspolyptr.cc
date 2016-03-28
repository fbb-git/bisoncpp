#include "parser.ih"

    // $nr. $-nr.
bool Parser::svsPolyPtr(int nElements, Block &block, AtDollar const &atd)
{
    return svsPolyReplace(nElements, block, atd, "->");
}
