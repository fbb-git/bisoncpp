#include "parser.ih"

void Parser::installAction(Block &block) 
{
                                    // process the block for the last
                                    // production rule, having a given number
                                    // of elements.

    substituteBlock(d_rules.nElements(), block);
    d_rules.setAction(block);
}

