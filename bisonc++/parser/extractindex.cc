#include "parser.hh"

size_t Parser::extractIndex(int *idx, size_t pos)
{
    istringstream is(d_scanner.block().substr(pos));

    is >> *idx;
    return is.tellg();
}
