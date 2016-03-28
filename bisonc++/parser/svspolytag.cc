#include "parser.ih"

    // $<TAG>-nr
bool Parser::svsPolyTag(int nElements, Block &block,AtDollar const &atd)
{
    return svsPolyTagReplace(nElements, block, atd, "");
}
