#include "parser.ih"

    // $$.
bool Parser::dvalPolyMem(int nElements, Block &block,AtDollar const &atd)
{
    return dvalPolyReplace(nElements < 0, block, atd, ".");
}
