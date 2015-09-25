#include "options.ih"

void Options::setRequiredTokens(size_t nRequiredTokens)
{
    if (d_requiredTokens != 0)
        emsg << "%required-tokens multiply specified " << endl;
    else
        d_requiredTokens = nRequiredTokens;
}
