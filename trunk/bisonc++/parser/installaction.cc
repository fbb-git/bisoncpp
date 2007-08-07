#include "parser.ih"

void Parser::installAction(Block &block) 
{
                                    // process the block for the last
                                    // production rule, having a given number
                                    // of elements. Returns false if no
                                    // explicit return was defined
    if (!substituteBlock(d_rules.nElements(), block))
        checkFirstType();
        
    d_rules.setAction(block);
}

