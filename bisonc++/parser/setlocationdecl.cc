#include "parser.ih"

// copy the location declaration into ostringstream `location_decl' as the
// definition of LSTYPE.

void Parser::setLocationDecl()
{
    if (d_locationDecl.size())
        lineMsg() << "%location-struct or %ltype multiply declared" << err;

    d_locationDecl = "struct LTYPE\n";

    if (!d_scanner.block(&d_block))
        lineMsg() << "`%locationstruct { ... }' expected" << err;
    else
        (d_locationDecl += d_block) += ";\n";

    if (d_scanner.lex() != ';')                     // trailing ; is ok
        d_scanner.unget();                          // but none is ok too.

    d_lspNeeded = true;
}
