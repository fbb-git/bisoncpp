#include "parser.ih"

    // see parser.h about refByScanner for info why nElements < 0 
    // returns true.

    // $$
bool Parser::dvalRefUnion(int nElements, Block &block, AtDollar const &atd)
{
    return 
        atd.refByScanner() ?
            dvalUnionReplace(nElements < 0, block, atd, "")
        :
            dvalReplace(false, block, atd, "")  or  nElements < 0;
}
