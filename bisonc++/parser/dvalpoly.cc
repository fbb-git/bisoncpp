#include "parser.ih"

    // $$
bool Parser::dvalPoly(int nElements, Block &block, AtDollar const &atd)
{
    return dvalPolyReplace(block, atd, "");
}
