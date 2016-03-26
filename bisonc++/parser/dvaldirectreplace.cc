#include "parser.ih"

bool Parser::dvalDirectReplace(Block &block, AtDollar const &atd, 
                                                        char const *suffix)
{
    ostringstream  replacement;
    
    replacement << s_semanticValue << suffix;

    block.replace(atd.pos(), atd.length(), replacement.str());

    return false;
}
