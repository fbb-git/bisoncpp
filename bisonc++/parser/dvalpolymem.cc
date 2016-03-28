#include "parser.ih"

    // $$.
bool Parser::dvalPolyMem(int nElements, Block &block,AtDollar const &atd)
{
    return dvalPolyReplace(block, atd, ".");
}
