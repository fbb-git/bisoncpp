#include "parser.ih"

// Only with %type a symbol may already exist. 
//
// Symbols are defined by %token, %left etc. as terminals only.
//
// At a %type declaration, their types can be set, but only if their types
// haven't been set yet. 
// 
// A %type can also define an undetermined nonterminal: eventually 
// it must be defined as a nonterminal by a rule.
//
// If a %type is followed by a %token etc. then those latter directives may
// change the kind to symbol into terminal, but not their type.
// 
// This function is called by the `symbol' rule

//  Unknown symbol:
//
//  Define the terminal as UNDETERMINED with %type, otherwise as `type'
//
//  known symbol:
//  ---------------------------------------------------------------------
//                      Second: 
//              ---------------------------------------------------------
//              %token          %type (-> d_typeDirective)
//  ---------------------------------------------------------------------
//  First:
//  (%type -> UNDETERMINED)
//  ---------------------------------------------------------------------
//      %token  mult.def'd      OK, unless token's %type is specified
//                              and different from %type. If equal: warn
//
//      %type   OK, same as     OK, same as upper right
//              upper right
//  ---------------------------------------------------------------------


void Parser::defineTerminal(string const &name, Symbol::Type type)
{
    if (Symbol *sp = d_symtab.lookup(name))     // known symbol?
    {
            // known symbol: upper left alternative
        if (not sp->isUndetermined() && not d_typeDirective)
        {
            multiplyDefined(sp);
            return;
        }

        if (sp->sType().empty())
            sp->setStype(d_field);

        else if (sp->sType() == d_field)
            wmsg << 
                        '`' << name << "' type repeatedly specified as <" <<
                        d_field << ">" << endl;

        else    // type clash
            emsg << 
                        "can't redefine type <" << sp->sType() << "> of `" <<
                        name << "' to <" << d_field << ">" << endl;
    }

    else // new symbol: insert it as (provisional or definitive) terminal
        d_symtab.insert
        (
            Symtab::value_type
            (
                name, 
                d_rules.insert
                (
                    new Terminal(name, 
                                    d_typeDirective ? 
                                        Symbol::UNDETERMINED 
                                    :
                                        type, 
                                    type == Symbol::CHAR_TERMINAL ?
                                        d_scanner.number()
                                    :
                                        Terminal::DEFAULT, 
                                    d_association, d_field),
                    d_matched
                )
            )
        );
}
