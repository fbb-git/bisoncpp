#include "parser.ih"

void Parser::setStype()
{
    if (d_stackDecl.size())
        lineMsg() << "%union or %stype multiply declared" << err;
    
    d_stackDecl = "typedef ";

    if (d_scanner.lex() == Scanner::IDENTIFIER)
    {
        string const &type = d_scanner.trimmedText();
        if (type.length())
        {
            (d_stackDecl += type) += " STYPE;\n";
            return;
        }
    }

   lineMsg() << "`%stype type-definition' expected" << err;
}
