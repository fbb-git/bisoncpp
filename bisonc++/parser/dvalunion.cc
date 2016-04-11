#include "parser.ih"

    // $$
bool Parser::dvalUnion(int nElements, Block &block, AtDollar const &atd)
{
    return dvalUnionReplace(nElements < 0, block, atd, "");
}
