#include "parser.ih"

bool Parser::svsDirectPtr(int nElements, Block &block,AtDollar const &atd)
{
    return svsDirectReplace(nElements, block, atd, "->");
}
