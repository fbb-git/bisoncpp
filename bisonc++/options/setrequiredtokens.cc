#include "options.ih"

void Options::setRequiredTokens()
{
    if (d_requiredTokens != 0)
        emsg << "%required-tokens multiply specified " << endl;
    else
        d_requiredTokens = A2x(*d_matched);
}
