#include "generator.ih"

bool Generator::ifPrintTokens() const
{
    return d_arg.option(0, "printtokens");
}
