#include "parser.ih"

// copy the location declaration into `d_locationDecl' as the
// definition of LSTYPE.

void Parser::setLocationDecl()
{
    if (d_locationDecl.size())
        lineMsg(emsg) << "%location-struct or %ltype multiply specified" << 
                                                                        endl;
    
    (d_locationDecl = "struct LTYPE__\n" + d_scanner.block().str()) += ";\n";

    d_lspNeeded = true;
}
