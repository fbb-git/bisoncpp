#include "parser.ih"

void Parser::list()
{
    if (!d_symtab.size())
        cout << "No variables\n";
    else
        for_each(d_symtab.begin(), d_symtab.end(), ShowVar(d_value));
}
