#include "parser.ih"

Symbol *Parser::useSymbol() 
{
    string const &name = d_scanner.text();

    if (Symbol *sp = d_symtab.lookup(name))
        return sp;

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
