#include "parser.ih"

    // $nr. $-nr.
bool Parser::svsUnionMem(int nElements, Block &block, AtDollar const &atd)
{
    return svsUnionReplace(nElements, block, atd, ".");
}
