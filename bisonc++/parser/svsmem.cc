#include "parser.ih"

    // $nr. $-nr.
bool Parser::svsMem(int nElements, Block &block, AtDollar const &atd)
{
    return svsReplace(nElements, block, atd, ".");
}
