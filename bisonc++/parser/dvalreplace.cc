#include "parser.ih"

bool Parser::dvalReplace(Block &block, AtDollar const &atd, 
                                                        char const *suffix)
{
    block.replace(atd.pos(), atd.length(), s_semanticValue + suffix);
    return block.assignment();
}
