#include "parser.ih"

    // $<TAG>-nr.
bool Parser::svsUnionTagPtr(int nElements, Block &block,AtDollar const &atd)
{
    return svsUnionTagReplace(nElements, block, atd, "->");
}
