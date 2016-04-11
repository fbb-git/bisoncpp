#include "parser.ih"

    // $$
bool Parser::dvalPoly(int nElements, Block &block, AtDollar const &atd)
{
                            // < 0 means: mid-rule action
    return dvalPolyReplace(nElements < 0, block, atd, "");
}
