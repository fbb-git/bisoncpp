#include "parser.ih"

bool Parser::dvalDirectMem(int nElements, Block &block, AtDollar const &atd)
{
    return dvalDirectReplace(block, atd, ".");
}
