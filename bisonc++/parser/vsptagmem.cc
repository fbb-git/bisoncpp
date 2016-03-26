#include "parser.ih"

bool Parser::vspTagMem(int nElements, Block &block,AtDollar const &atd)
{
    return vspTagReplace(nElements, block, atd, ".");
}
