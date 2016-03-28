#include "parser.ih"

    // $<TAG>-nr.
bool Parser::svsUnionTagMem(int nElements, Block &block,AtDollar const &atd)
{
    return svsUnionTagReplace(nElements, block, atd, ".");
}
