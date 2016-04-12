#include "parser.ih"

    // $$.
bool Parser::dvalMem(int nElements, Block &block,AtDollar const &atd)
{
    return dvalReplace(nElements < 0, block, atd, ".");
}
