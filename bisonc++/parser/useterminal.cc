#include "parser.ih"

Terminal *Parser::useTerminal() 
{
    string const &name = d_scanner.canonicalQuote();

    if (Symbol *sp = d_symtab.lookup(name))
    {
        if (sp->isTerminal())
            return Terminal::downcast(sp);

        multiplyDefined(sp);
        return 0;
    }

    Terminal *tp = new Terminal(name, Symbol::CHAR_TERMINAL, 
                                      d_scanner.number());
    d_symtab.insert
    (
        Symtab::value_type
        (
            name, 
            d_rules.insert(tp, d_matched)
        )
    );

    return tp;
}
