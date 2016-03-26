#include "parser.ih"

bool Parser::dvalRef(int nElements, Block &block, AtDollar const &atd)
{
    return dvalReplace(block, atd, "");
}
