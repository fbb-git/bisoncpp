#include "parser.ih"

bool Parser::vspMem(int nElements, Block &block,AtDollar const &atd)
{
    return vspReplace(nElements, block, atd, ".");
}
