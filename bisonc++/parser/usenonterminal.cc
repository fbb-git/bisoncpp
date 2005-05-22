#include "parser.ih"

NonTerminal *Parser::useNonTerminal()
{
    string const &name = d_scanner.text();

    if (Symbol *sp = d_symtab.lookup(name))
    {
        if (sp->isNonTerminal())
            return NonTerminal::downcast(sp);

        multiplyDefined(sp, name);
        return 0;
    }

    NonTerminal *np = new NonTerminal(name);

    d_symtab.insert
    (
        Symtab::value_type
        (
            name, 
            d_rules.insert(np)
        )
    );

    return np;
}
