#include "parser.ih"

// If the symbol already exists, that's ok, but it is then required that 
// the symbol's type is empty, since we're going to set it here

// if the symbol doesn't exist yet, set it now as a (for the time being)
// non-terminal. Later declarations may change these provisional nonterminals
// into terminals, in particular in the defineTerminal() function.
// This happens if %type is used before a %token/%left/... declaration.

void Parser::tryNonTerminal(string const &name, string const &stype)
{
    if (Symbol *sp = d_symtab.lookup(name))
    {
        if (sp->sType().empty())
            sp->setStype(stype);
        else
            multiplyDefined(sp, name);

        return;
    }

    NonTerminal *np = new NonTerminal(name, stype, Symbol::UNDETERMINED);

    d_symtab.insert
    (
        Symtab::value_type
        (
            name, 
            d_rules.insert(np)
        )
    );
}
