#include "parser.ih"

bool Parser::svsRef(int nElements, Block &block,AtDollar const &atd)
{
    return svsReplace(nElements, block, atd, "");
}
