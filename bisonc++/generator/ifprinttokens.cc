#include "generator.ih"

void Generator::ifPrintTokens(bool &accept) const
{
    accept = d_arg.option(0, "printtokens");
}
