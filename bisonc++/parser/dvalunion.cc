#include "parser.ih"

    // $$
bool Parser::dvalUnion(int nElements, Block &block, AtDollar const &atd)
{
cerr << "dvalunion\n";
    return dvalUnionReplace(block, atd, "");
}
