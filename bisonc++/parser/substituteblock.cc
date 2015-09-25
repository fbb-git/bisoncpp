#include "parser.ih"

// Stack_offset is the number of values in the current alternative so far, so
// it is d_elements.size(). It indicates where to find $0 with respect to the 
// top of the (?) stack. 
// If nElements is negative then this is a mid-action block, automatically
// resulting in negative dollar indices

bool Parser::substituteBlock(int nElements, Block &block)
{
        // Look for special characters. Do this from the end of the
        // block-text to the beginning, to keep the positions of earlier
        // special characters unaltered.

    bool explicitReturn = false;            // block return type as yet
                                            // unknown

    for (auto &atd: ranger(block.rbeginAtDollar(), block.rendAtDollar()))
    {
        switch (atd.type())
        {
            case AtDollar::DOLLAR:
                explicitReturn |= handleDollar(block, atd, nElements);
            break;

            case AtDollar::AT:
                handleAtSign(block, atd, nElements); 
            break;
        }
    }
                                            // save the default $1 value
                                            // at the beginning of a mid-rule
    if (nElements < 0)                      // action block
        saveDollar1(block, indexToOffset(1, nElements));

    if (not explicitReturn and d_arg.option('N') and d_rules.sType() != "")
        wmsg << "rule " << &d_rules.lastProduction() << 
            ": action block does not assign a(n) " << d_rules.sType() << 
                    " value to $$." << endl;

    return explicitReturn;
}

