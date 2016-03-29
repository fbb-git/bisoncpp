#include "parser.ih"

    // $$(
bool Parser::dvalPar(int nElements, Block &block, AtDollar const &atd)
{
    return dvalReplace(block, atd, "(");
}
