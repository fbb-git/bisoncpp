#include "parser.ih"

    // $<TAG>-nr
bool Parser::svsUnionTag(int nElements, Block &block,AtDollar const &atd)
{
    return svsUnionTagReplace(nElements, block, atd, "");
}
