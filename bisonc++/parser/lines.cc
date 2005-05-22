#include "parser.ih"

bool Parser::lines() const
{
    return !d_arg.option(0, "no-lines") &&
        (d_arg.option('l') || d_lines);
}
