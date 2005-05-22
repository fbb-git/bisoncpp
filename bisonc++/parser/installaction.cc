#include "parser.ih"

void Parser::installAction() 
{
    if (!d_block.length())          // No block, no installation
        return;
                                    // process the block for the last
                                    // production rule, having a given number
                                    // of elements. 
    substituteBlock(d_rules.nElements());
    d_rules.setAction(d_block);
    d_block.clear();
}

