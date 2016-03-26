#include "parser.ih"

bool Parser::svsTagReplace(int nElements, Block &block,AtDollar const &atd, 
                           char const *suffix)
{
    if (checkExistingTag(atd))
    {
        warnNegativeDollarIndices(atd);

        ostringstream  replacement;
        replacement << svsElement(nElements, atd) << ".get<Tag__::" << 
                                            atd.tag() << ">()" << suffix;
    
        block.replace(atd.pos(), atd.length(), replacement.str());
    }
    return false;
}
