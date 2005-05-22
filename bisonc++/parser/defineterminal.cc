#include "parser.ih"

// If a symbol has already been defined as a undetermined nonterminal, then
// remove the nonterminal, and change it into a terminal, having the same
// stype as the (now deleted) nonterminal. 
// This happens if a %type declaration preceded the corresponding %token/%left
// declaration. 

void Parser::defineTerminal(string const &name, 
                            Symbol::Type type,
                            Terminal::Association association, 
                            string stype)
{
    string literal = d_scanner.text();

    if (Symbol *sp = d_symtab.lookup(name))
    {
        if 
        (
            sp->isUndetermined()
            &&
            (
                stype.empty()
                ||
                stype == sp->sType()
            )
        )
        {
            stype = sp->sType();
            d_symtab.erase(d_symtab.find(name));
            d_rules.remove(NonTerminal::downcast(sp));
        }
        else
        {
            multiplyDefined(sp, literal);
            return;
        }
    }

    d_symtab.insert
    (
        Symtab::value_type
        (
            name, 
            d_rules.insert
            (
                new Terminal(name, type, 
                                type == Symbol::CHAR_TERMINAL ?
                                    d_scanner.number()
                                :
                                    Terminal::DEFAULT, 
                                association, stype),
                literal
            )
        )
    );
}
