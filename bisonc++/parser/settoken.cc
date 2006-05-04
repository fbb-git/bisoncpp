#include "parser.ih"

void Parser::setToken()
{
    string stype;
    if (d_scanner.lex() == Scanner::TYPENAME)
        getType(&stype);
    else
        d_scanner.unget();

    while (true)
    {
        switch (d_scanner.lex())
        {
            case ';':
            return;

            default:
                d_scanner.unget();
            return;

            case ',':
            break;

            case Scanner::IDENTIFIER:
                defineTerminal(d_scanner.text(), Symbol::SYMBOLIC_TERMINAL,
                               Terminal::UNDEFINED, stype);
//, Terminal::ACTIVE);
                d_rules.setLastPriority(0);
            continue;

            case Scanner::NUMBER:
                d_rules.setLastTerminalValue(d_scanner.number());
            break;
        }
    }
}





