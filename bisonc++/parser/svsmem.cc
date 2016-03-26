#include "parser.ih"

bool Parser::svsMem(int nElements, Block &block,AtDollar const &atd)
{
    return svsReplace(nElements, block, atd, ".");
}
