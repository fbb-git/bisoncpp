#include "parser.ih"

// copy the location declaration into `d_locationDecl' as the
// definition of LSTYPE.

void Parser::setLocationDecl()
{
    d_options.setLocationDecl(d_scanner.block().str());
    d_lspNeeded = true;
}
