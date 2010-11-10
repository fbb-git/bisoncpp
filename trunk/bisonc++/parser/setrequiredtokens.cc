#include "parser.ih"

void Parser::setRequiredTokens()
{
    if (!d_arg.option(0, "required-tokens"))
        d_requiredTokens = d_scanner.number();
}
