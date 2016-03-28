#include "parser.ih"

bool Parser::svsReplace(int nElements, Block &block,AtDollar const &atd, 
                                                        char const *suffix)
{
    warnNegativeDollarIndices(atd);

    block.replace(atd.pos(), atd.length(), 
                             svsElement(nElements, atd.nr()) + suffix);
    return false;
}
