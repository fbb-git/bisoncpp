#include "parser.ih"

bool Parser::dvalDirectPtr(int nElements, Block &block, AtDollar const &atd)
{
    return dvalDirectReplace(block, atd, "->");
}
