#include "parser.ih"

bool Parser::svsDirectMem(int nElements, Block &block,AtDollar const &atd)
{
    return svsDirectReplace(nElements, block, atd, ".");
}
