#include "parser.ih"

    // _$$
bool Parser::dval(int nElements, Block &block, AtDollar const &atd)
{
    return dvalReplace(nElements < 0 && atd.refByScanner(), block, atd, "");
}
