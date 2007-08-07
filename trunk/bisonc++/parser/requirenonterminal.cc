#include "parser.ih"

NonTerminal *Parser::requireNonTerminal(string const &name)
{
    string stype;
    Symbol *sp = d_symtab.lookup(name);

    if (sp)
    {
        if (sp->isNonTerminal())                // Only ok if already defined
            return NonTerminal::downcast(sp);   // as non-terminal

        if (sp->isUndetermined())               // assumed terminal earlier, 
        {                                       // turns out to be nonterm.
            stype = sp->sType();
            d_symtab.erase(d_symtab.find(name));

// now all occurrences of the terminal in existing production rules
// must be changed into nonterminals. Also, sp must be removed from rule's
// terminal vector d_terminal

        }
        else
        {
            multiplyDefined(sp);
            return 0;
        }
    }

    NonTerminal *np = new NonTerminal(name, stype);
                                                // If not yet defined, define
                                                // it now as a non-terminal
    d_symtab.insert
    (
        Symtab::value_type
        (
            name, 
            d_rules.insert(np)
        )
    );

    if (sp)
        d_rules.termToNonterm(sp, np);

    return np;
}

