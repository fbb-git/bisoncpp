#include "parser.ih"

bool Parser::vspRef(int nElements, Block &block,AtDollar const &atd)
{
    return vspReplace(nElements, block, atd, "");
}
