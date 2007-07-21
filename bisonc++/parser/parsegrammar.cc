#include "parser.ih"

    // the effect of parseGrammar() is to eat the grammar until the first
    // nonTerminal, and then to process that nonTerminal.
void Parser::parseGrammar()
{
    bool ignore = false;

    d_block.clear();            // maybe leftover from %union or %loc.struct

    while (true)
    {
        switch (d_scanner.lex())
        {
            case Scanner::TWO_PERCENTS:
            case Scanner::ENDFILE:
                checkEndOfRule();
            return;

            case Scanner::RULE:
                ignore = false;
                parseRule();    // handle all rules. Start by defining this
            break;              // rule, and continue until the next

            default:            // eat all unexpected symbols and report the
                if (!ignore)    // first of a series. Reset to normal at the
                {               // next RULE token
                    ignore = true;
                    lineMsg() << "Unexpected `" << 
                            d_scanner.text() << 
                            "' encountered in the rule section" << err;
                }            
            break;                
        }
    }
}
