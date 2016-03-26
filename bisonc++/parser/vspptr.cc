#include "parser.ih"

bool Parser::vspPtr(int nElements, Block &block,AtDollar const &atd)
{
    return vspReplace(nElements, block, atd, "->");
}
