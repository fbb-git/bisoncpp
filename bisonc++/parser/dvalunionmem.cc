#include "parser.ih"

    // $$.
bool Parser::dvalUnionMem(int nElements, Block &block,AtDollar const &atd)
{
    return dvalUnionReplace(block, atd, ".");
}
