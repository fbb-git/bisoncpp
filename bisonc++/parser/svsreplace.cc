#include "parser.ih"

bool Parser::svsReplace(int nElements, Block &block,AtDollar const &atd, 
                                                        char const *suffix)
{
    string tag = checkRuleTag(atd);

    if (not tag.empty())
    {
        warnNegativeDollarIndices(atd);

        ostringstream  replacement;
        replacement << svsElement(nElements, atd) << ".get<Tag__::" << 
                                                    tag << ">()" << suffix;

        block.replace(atd.pos(), atd.length(), replacement.str());
    }
    return false;
}
