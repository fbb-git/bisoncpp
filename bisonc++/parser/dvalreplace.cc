#include "parser.ih"

bool Parser::dvalReplace(Block &block, AtDollar const &atd, 
                                                        char const *suffix)
{
    string tag = checkRuleTag(atd);

    if (not tag.empty())
    {
        ostringstream  replacement;
        
        replacement << s_semanticValue <<
                                ".get<Tag__::" << tag << ">()" << suffix;

        block.replace(atd.pos(), atd.length(), replacement.str());
    }

    return false;
}
