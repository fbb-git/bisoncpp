#include "parser.ih"

void Parser::setType()
{
    if (d_scanner.lex() != Scanner::TYPENAME)
    {
        lineMsg() << 
                            "`%type <IDENTIFIER> token(s)' expected" << err;
        d_scanner.ignoreUntilEndl();
        return;
    }
        
    string stype;
    getType(&stype);

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
            continue;

            case Scanner::IDENTIFIER:
                tryNonTerminal(d_scanner.text(), stype);
            continue;
        }
    }
}





