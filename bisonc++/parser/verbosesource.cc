#include "parser.ih"

string Parser::verboseSource() const
{
    return d_arg.option('V') ? verbose() : "";
}
