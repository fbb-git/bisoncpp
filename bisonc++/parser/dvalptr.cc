#include "parser.ih"

bool Parser::dvalPtr(int nElements, Block &block,AtDollar const &atd)
{
    return dvalReplace(block, atd, "->");
}
