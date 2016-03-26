#include "parser.ih"

bool Parser::vspTagRef(int nElements, Block &block,AtDollar const &atd)
{
    return vspTagReplace(nElements, block, atd, "");
}
