#include "parser.ih"

bool Parser::dvalMem(int nElements, Block &block, AtDollar const &atd)
{
    return dvalReplace(block, atd, ".");
}
