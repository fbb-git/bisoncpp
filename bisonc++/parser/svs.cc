#include "parser.ih"

bool Parser::svs(int nElements, Block &block,AtDollar const &atd)
{
    return svsReplace(nElements, block, atd, "");
}
