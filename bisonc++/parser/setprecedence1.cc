#include "parser.ih"

void Parser::setPrecedence()
{
    Symbol *sp;

    switch (d_scanner.lex())           // get the next token, following %prec
    {
        case Scanner::IDENTIFIER:
            sp = d_symtab.lookup(d_scanner.text());
        break;

        case Scanner::QUOTE:
            sp = d_symtab.lookup(d_scanner.canonicalQuote());
        break;

        default:
            lineMsg() << "`%prec <token>': token not specified" << err;
            d_scanner.unget();
        return;
    }        

    if (sp && sp->isTerminal())
        d_rules.setPrecedence(Terminal::downcast(sp));
    else
    {
        string const &name = d_scanner.text();
        lineMsg() << 
            "`%prec " << name << "': `" << name << 
            "' must be a declared terminal token" << err;
    }
}
