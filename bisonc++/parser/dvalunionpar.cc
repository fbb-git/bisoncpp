#include "parser.ih"

    // $$(
bool Parser::dvalUnionPar(int nElements, Block &block, AtDollar const &atd)
{
    return dvalReplace(nElements < 0, block, atd, "(");
}
