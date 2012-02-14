#include "parser.ih"

Symbol *Parser::useSymbol() 
{
    if (Symbol *sp = d_symtab.lookup(d_matched))
        return sp;

    NonTerminal *np = new NonTerminal(d_matched);

    d_symtab.insert
    (
        Symtab::value_type
        (
            d_matched, 
            d_rules.insert(np)
        )
    );

    return np;
}
