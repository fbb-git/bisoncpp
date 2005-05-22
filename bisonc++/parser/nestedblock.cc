#include "parser.ih"

// do nothing if *block is empty.  add a hidden rule consisting of one action
// block. Make sure that this rule is the next element in the currently
// defined rule production. Clear the block after processing.

void Parser::nestedBlock() 
{
    if (d_block.empty())
        return;

    string name = nextHiddenName();

    NonTerminal *np = NonTerminal::downcast(
                            defineNonTerminal(name, d_rules.sType())
                      );

    d_rules.addElement(np);             // add the block as a hidden rule

    substituteBlock(0);                 // process the block for 0 production
                                        // elements.

    d_rules.setHiddenAction(d_block);   // define the action in the hidden
                                        // terminal's production rule

    lineMsg() << "Adding hidden non-terminal " << name << 
                " for the block\n" << d_block << info;

    d_block.erase();
}
