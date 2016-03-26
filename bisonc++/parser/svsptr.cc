#include "parser.ih"

bool Parser::svsPtr(int nElements, Block &block,AtDollar const &atd)
{
    return svsReplace(nElements, block, atd, "->");
}
