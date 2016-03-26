#include "parser.ih"

bool Parser::vspTagPtr(int nElements, Block &block,AtDollar const &atd)
{
    return vspTagReplace(nElements, block, atd, "->");
}
