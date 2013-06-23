#include "options.ih"

void Options::setPrintTokens()
{
    d_printTokens = true;
    d_warnOptions.insert("print-tokens");
}


