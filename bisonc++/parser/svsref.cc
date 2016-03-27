#include "parser.ih"

bool Parser::svsRef(int nElements, Block &block,AtDollar const &atd)
{
    warnNegativeDollarIndices(atd);

    block.replace(atd.pos(), atd.length(), svsElement(nElements, atd));
    return false;
}
