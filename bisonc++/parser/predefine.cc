#include "parser.ih"

void Parser::predefine(Terminal const *terminal)
{
    d_symtab.insert
    (
        Symtab::value_type
        (
            terminal->name(), 
            d_rules.insert(const_cast<Terminal *>(terminal), terminal->name())
        )
    ).first->second->used();
}
