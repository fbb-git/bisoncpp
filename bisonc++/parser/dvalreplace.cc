#include "parser.ih"

bool Parser::dvalReplace(bool midRule, Block &block, AtDollar const &atd, 
                         char const *suffix, char const *label)
{
    warnAutoTag(midRule, atd, label);
    
    block.replace(atd.pos(), atd.length(), s_semanticValue + suffix);

    return block.assignment();
}
