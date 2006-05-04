#include "parser.ih"

Terminal *Parser::useTerminal() 
{
    static Terminal *tp;

    string const &name = d_scanner.canonicalQuote();

    if (Symbol *sp = d_symtab.lookup(name))
    {
        if (sp->isTerminal())
        {
            tp = Terminal::downcast(sp);
            return tp;
        }

        multiplyDefined(sp, name);
        return 0;
    }

    tp = new Terminal(name, Symbol::CHAR_TERMINAL, d_scanner.number());

    d_symtab.insert
    (
        Symtab::value_type
        (
            name, 
            d_rules.insert(tp, d_scanner.text())
        )
    );

    return tp;
}
