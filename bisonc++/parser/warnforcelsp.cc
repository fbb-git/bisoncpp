#include "parser.ih"

void Parser::warnForceLSP(size_t lineNr) const
{
    if (not d_options.lspNeeded())
    {
        wmsg << "@ used at line " << lineNr << ": %lsp-needed forced" << 
                endl;
        d_options.setLspNeeded();
    }
}
