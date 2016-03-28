#include "parser.ih"

    // $$
bool Parser::dvalUnion(int nElements, Block &block, AtDollar const &atd)
{
    return dvalUnionReplace(block, atd, "");
}
