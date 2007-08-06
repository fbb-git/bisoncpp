#include "parser.ih"

// Add a hidden rule consisting of one action block. 

void Parser::nestedBlock(Block &block) 
{
    string name = nextHiddenName();

    // Since the inner block is a block, simply assume that its return value
    // matches the type of the rule in which it is nested.
    NonTerminal *np = NonTerminal::downcast(
                            defineNonTerminal(name, d_rules.sType())
                      );

    d_rules.addElement(np);             // add the block as a hidden rule

    substituteBlock(0, block);          // process the block for 0 production
                                        // elements.

    d_rules.setHiddenAction(block);     // define the action in the hidden
                                        // terminal's production rule

    lineMsg() << "Adding hidden non-terminal " << name << 
                " for the block\n" << block << info;
}
