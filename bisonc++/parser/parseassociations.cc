#include "parser.ih"

// read in a %left, %right or %nonassoc declaration and record its
// information.

void Parser:: parseAssociations(Terminal::Association association)
{
    Terminal::incrementPrecedence();

    string stype;

    while (true)
    {
        switch (d_scanner.lex())
        {
            default:
                d_scanner.unget();      // reset the token to be read again
            return;

            case ';':
            return;
    
            case Scanner::TYPENAME:
                getType(&stype);
            break;

            case ',':
            break;
    
            case Scanner::QUOTE:
                defineTerminal(d_scanner.canonicalQuote(), 
                                Symbol::CHAR_TERMINAL, association, stype);
            continue;
            
            case Scanner::IDENTIFIER:
                defineTerminal(d_scanner.text(), Symbol::SYMBOLIC_TERMINAL,
                                association, stype);
            continue;

            case Scanner::NUMBER:
                d_rules.setLastTerminalValue(d_scanner.number());
            break;
        }
    }
}






