#include "parser.ih"

    // $$
bool Parser::dvalRefUnion(int nElements, Block &block, AtDollar const &atd)
{
    return 
        atd.refByScanner() ?
            dvalUnionReplace(nElements < 0, block, atd, "")
        :
            dvalReplace(nElements < 0, block, atd, "", "field");
}
