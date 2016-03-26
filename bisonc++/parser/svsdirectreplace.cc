#include "parser.ih"

bool Parser::svsDirectReplace(int nElements, Block &block,AtDollar const &atd, 
                                                        char const *suffix)
{
    warnNegativeDollarIndices(atd);

    ostringstream  replacement;
    replacement << svsElement(nElements, atd) << suffix;

    block.replace(atd.pos(), atd.length(), replacement.str());

    return false;
}
