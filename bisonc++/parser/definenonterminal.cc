#include "parser.ih"

Symbol *Parser::defineNonTerminal(string const &name, string const &stype)
{
    if (Symbol *sp = d_symtab.lookup(name))
    {
        multiplyDefined(sp);
        return 0;
    }

    NonTerminal *np = new NonTerminal(name, stype);

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
