#include "parser.ih"

    // $<TAG>-nr.
bool Parser::svsPolyTagPtr(int nElements, Block &block,AtDollar const &atd)
{
    return svsPolyTagReplace(nElements, block, atd, "->");
}
